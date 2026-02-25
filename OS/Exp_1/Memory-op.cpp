#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// 全局变量
HANDLE hSemaphore;
HANDLE hMutex; // 用于保护共享数据
vector<LPVOID> memoryBlocks; // 存储保留区域地址
SYSTEM_INFO sysInfo;

// 权限映射
DWORD GetProtection(int protId) {
    switch (protId) {
        case 0: return PAGE_READONLY;
        case 1: return PAGE_READWRITE;
        case 2: return PAGE_EXECUTE;
        case 3: return PAGE_EXECUTE_READ;
        case 4: return PAGE_EXECUTE_READWRITE;
        default: return PAGE_READWRITE;
    }
}

struct MemoryOperation {
    int time;
    int blocks;
    int opCode;
    SIZE_T size;
    int protection;
};

vector<MemoryOperation> operations;

// 加载操作文件
bool LoadOperations(const string& filename) {
    ifstream in(filename);
    if (!in) return false;

    string line;
    while (getline(in, line)) {
        MemoryOperation op;
        stringstream ss(line);
        ss >> op.time >> op.blocks >> op.opCode >> op.size >> op.protection;
        operations.push_back(op);
    }
    return true;
}

DWORD WINAPI MemoryThread(LPVOID) {
    for (const auto& op : operations) {
        Sleep(op.time);
        DWORD prot = GetProtection(op.protection);

        for (int i = 0; i < op.blocks; ++i) {
            LPVOID addr = nullptr;

            switch (op.opCode) {
                case 0: // reserve
                    addr = VirtualAlloc(nullptr, op.size, MEM_RESERVE, prot);
                    cout << "[RESERVE] ";
                    if (addr) {
                        WaitForSingleObject(hMutex, INFINITE);
                        memoryBlocks.push_back(addr);
                        ReleaseMutex(hMutex);
                        cout << "Reserved " << op.size << " bytes at " << addr << ", Protection: " << op.protection << "\n";
                    } else {
                        cout << "Reserve failed for size " << op.size << "\n";
                    }
                    break;

                case 1: // commit
                    if (!memoryBlocks.empty()) {
                        WaitForSingleObject(hMutex, INFINITE);
                        addr = VirtualAlloc(memoryBlocks.back(), op.size, MEM_COMMIT, prot);
                        if (addr) {
                            cout << "[COMMIT] Committed " << op.size << " bytes at " << addr << ", Protection: " << op.protection << "\n";
                        } else {
                            cout << "[COMMIT] Failed to commit memory\n";
                        }

                        // 仅当权限为可写时才写入内存，防止访问违规
                        if (addr && (prot == PAGE_READWRITE || prot == PAGE_EXECUTE_READWRITE)) {
                            memset(addr, 1, op.size); // 写入每个字节，触发物理页分配
                        }

                        ReleaseMutex(hMutex);
                    }

                    break;


                case 2: // decommit
                    if (!memoryBlocks.empty()) {
                        BOOL success = VirtualFree(memoryBlocks.back(), op.size, MEM_DECOMMIT);
                        cout << "[DECOMMIT] " << (success ? "Decommitted" : "Failed to decommit") << " " << op.size << " bytes at " << memoryBlocks.back() << "\n";
                    }
                    break;

                case 3: // release
                    if (!memoryBlocks.empty()) {
                        WaitForSingleObject(hMutex, INFINITE);
                        LPVOID releaseAddr = memoryBlocks.back();
                        BOOL success = VirtualFree(releaseAddr, 0, MEM_RELEASE);
                        if (success) {
                            cout << "[RELEASE] Released memory at " << releaseAddr << "\n";
                            memoryBlocks.pop_back();
                        } else {
                            cout << "[RELEASE] Failed to release memory at " << releaseAddr << "\n";
                        }
                        ReleaseMutex(hMutex);
                    }
                    break;

                case 4: // lock
                    if (!memoryBlocks.empty()) {
                        BOOL success = VirtualLock(memoryBlocks.back(), op.size);
                        cout << "[LOCK] " << (success ? "Locked" : "Failed to lock") << " " << op.size << " bytes at " << memoryBlocks.back() << "\n";
                    }
                    break;

                case 5: // unlock
                    if (!memoryBlocks.empty()) {
                        BOOL success = VirtualUnlock(memoryBlocks.back(), op.size);
                        cout << "[UNLOCK] " << (success ? "Unlocked" : "Failed to unlock") << " " << op.size << " bytes at " << memoryBlocks.back() << "\n";
                    }
                    break;

                default:
                    cout << "[UNKNOWN OPERATION] Code: " << op.opCode << "\n";
                    break;
            }
        }

        // 通知监控线程
        ReleaseSemaphore(hSemaphore, 1, nullptr);
    }

    return 0;
}


// 跟踪线程
DWORD WINAPI MonitorThread(LPVOID) {
    MEMORYSTATUS memStatus;
    while (true) {
        WaitForSingleObject(hSemaphore, INFINITE);
        memStatus.dwLength = sizeof(memStatus);
        GlobalMemoryStatus(&memStatus);

        GetSystemInfo(&sysInfo);
        cout << "------ Monitor Info ------\n";
        cout << "Page size: " << sysInfo.dwPageSize << " bytes\n";
        cout << "Min addr: " << sysInfo.lpMinimumApplicationAddress << "\n";
        cout << "Max addr: " << sysInfo.lpMaximumApplicationAddress << "\n";
        cout << "Total Phys Mem: " << memStatus.dwTotalPhys / 1024 << " KB\n";
        cout << "Avail Phys Mem: " << memStatus.dwAvailPhys / 1024 << " KB\n";
        cout << "Total Virtual: " << memStatus.dwTotalVirtual / 1024 << " KB\n";
        cout << "Avail Virtual: " << memStatus.dwAvailVirtual / 1024 << " KB\n";
        cout << "--------------------------\n\n";

        if (memoryBlocks.empty()) break; // 所有内存释放后退出
    }
    return 0;
}

// 主函数
int main() {
    if (!LoadOperations("input.txt")) {
        cerr << "Failed to open input.txt\n";
        return 1;
    }

    hSemaphore = CreateSemaphore(nullptr, 0, 100, nullptr);
    hMutex = CreateMutex(nullptr, FALSE, nullptr);

    HANDLE allc = CreateThread(nullptr, 0, MemoryThread, nullptr, 0, nullptr);
    HANDLE trac = CreateThread(nullptr, 0, MonitorThread, nullptr, 0, nullptr);

    WaitForSingleObject(allc, INFINITE);
    WaitForSingleObject(trac, INFINITE);

    CloseHandle(allc);
    CloseHandle(trac);
    CloseHandle(hSemaphore);
    CloseHandle(hMutex);

    return 0;
}
