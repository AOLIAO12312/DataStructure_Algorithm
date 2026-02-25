#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stack>

using namespace std;

struct MemoryOperation {
    int time;
    int blocks;
    int opCode;
    size_t size;
    int protection;
};

int main() {
    srand((unsigned int)time(nullptr));
    ofstream out("input.txt");
    if (!out) {
        cerr << "Failed to open input.txt\n";
        return 1;
    }

    const int totalOps = 4; // 可以修改此处，控制总共生成至少多少条操作
    int currentTime = 0;
    stack<int> reservedStack; // 模拟 reserve 的栈
    vector<MemoryOperation> ops;

    for (int i = 0; i < totalOps; ++i) {
        MemoryOperation op;
        op.time = currentTime += (rand() % 200 + 100); // 100~300ms
        op.blocks = 1;
        op.size = 4096;
        op.protection = rand() % 5;

        int opCode;

        if (reservedStack.empty() || rand() % 2 == 0) {
            // 创建新 reserve 操作
            opCode = 0; // reserve
            reservedStack.push(1); // 表示我们有一个新的 reserve 地址
        } else {
            // 随机选择对已有地址的操作（不释放）
            int possibleOps[] = {1, 2, 4, 5}; // commit, decommit, lock, unlock
            opCode = possibleOps[rand() % 4];
        }

        op.opCode = opCode;
        ops.push_back(op);
    }

    // 为每个未释放的 reserve 添加 release 操作
    while (!reservedStack.empty()) {
        reservedStack.pop();
        MemoryOperation releaseOp;
        releaseOp.time = currentTime += 200;
        releaseOp.blocks = 1;
        releaseOp.opCode = 3; // release
        releaseOp.size = 0;
        releaseOp.protection = 0;
        ops.push_back(releaseOp);
    }

    // 写入文件
    for (const auto& op : ops) {
        out << op.time << " " << op.blocks << " "
            << op.opCode << " " << op.size << " "
            << op.protection << "\n";
    }

    out.close();
    cout << "input.txt has been wroten. Total " << ops.size() << " operations\n";
    return 0;
}
