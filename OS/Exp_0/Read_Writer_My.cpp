#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

#define READER 'R'
#define WRITER 'W'
#define MAX_THREAD_NUM 64
#define INTE_PER_SEC 1000
#define MAX_STR_LEN 32

struct ThreadInfo {
    int serial;
    char entity;     // 'R' for reader, 'W' for writer
    double delay;
    double persist;
};

class ReaderWriterProblem {
private:
    int readCount = 0;
    int writeCount = 0;
    HANDLE mutexReadCount;
    HANDLE mutexWrite;
    HANDLE mutexRead;
    HANDLE semaphoreWrite;
    HANDLE semaphoreRead;

public:
    ReaderWriterProblem() {
        mutexReadCount = CreateMutex(NULL, FALSE, "mutex_for_readcount");
        mutexWrite = CreateMutex(NULL, FALSE, "mutex_for_write");
        mutexRead = CreateMutex(NULL, FALSE, "mutex_for_read");
        semaphoreWrite = CreateSemaphore(NULL, 1, 1, "semaphore_write");
        semaphoreRead = CreateSemaphore(NULL, 1, 1, "semaphore_read");
    }

    ~ReaderWriterProblem() {
        CloseHandle(mutexReadCount);
        CloseHandle(mutexWrite);
        CloseHandle(mutexRead);
        CloseHandle(semaphoreWrite);
        CloseHandle(semaphoreRead);
    }

    void readerThread(ThreadInfo* info) {
        DWORD delay = (DWORD)(info->delay * INTE_PER_SEC);
        DWORD persist = (DWORD)(info->persist * INTE_PER_SEC);

        Sleep(delay*1000);
        printf("Reader thread %d sends the reading request.\n", info->serial);

        WaitForSingleObject(mutexReadCount, INFINITE);
        readCount++;
        if (readCount == 1) {
            WaitForSingleObject(semaphoreWrite, INFINITE);
        }
        ReleaseMutex(mutexReadCount);

        // Simulate reading
        printf("Reader thread %d begins to read.\n", info->serial);
        Sleep(persist*1000);
        printf("Reader thread %d finished reading.\n", info->serial);

        WaitForSingleObject(mutexReadCount, INFINITE);
        readCount--;
        if (readCount == 0) {
            ReleaseSemaphore(semaphoreWrite, 1, NULL);
        }
        ReleaseMutex(mutexReadCount);
    }

    void writerThread(ThreadInfo* info) {
        DWORD delay = (DWORD)(info->delay * INTE_PER_SEC);
        DWORD persist = (DWORD)(info->persist * INTE_PER_SEC);

        Sleep(delay*1000);
        printf("Writer thread %d sends the writing request.\n", info->serial);

        WaitForSingleObject(semaphoreWrite, INFINITE);

        // Simulate writing
        printf("Writer thread %d begins to write.\n", info->serial);
        Sleep(persist*1000);
        printf("Writer thread %d finished writing.\n", info->serial);

        ReleaseSemaphore(semaphoreWrite, 1, NULL);
    }

    void processThreads(char* file, bool isReaderPriority) {
        ifstream inFile(file);
        if (!inFile) {
            cout << "Error opening input file.\n";
            return;
        }

        ThreadInfo threadInfo[MAX_THREAD_NUM];
        HANDLE threads[MAX_THREAD_NUM];
        DWORD threadCount = 0;
        DWORD threadId;

        while (inFile >> threadInfo[threadCount].serial >> threadInfo[threadCount].entity >> threadInfo[threadCount].delay >> threadInfo[threadCount].persist) {
            threadCount++;
        }

        for (DWORD i = 0; i < threadCount; i++) {
            if (threadInfo[i].entity == READER || threadInfo[i].entity == 'r') {
                threads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(&ReaderWriterProblem::readerThread), &threadInfo[i], 0, &threadId);
            } else {
                threads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(&ReaderWriterProblem::writerThread), &threadInfo[i], 0, &threadId);
            }
        }

        WaitForMultipleObjects(threadCount, threads, TRUE, INFINITE);

        cout << "All reader and writer threads have finished their operations.\n";
    }
};

void displayMenu() {
    printf("**********************************************************************\n");
    printf("1: Reader Priority\n");
    printf("2: Writer Priority\n");
    printf("3: Exit\n");
    printf("**********************************************************************\n");
    printf("Enter your choice (1, 2 or 3): ");
}

int main(int argc, char* argv[]) {
    char choice;
    ReaderWriterProblem problem;

    while (true) {
        displayMenu();

        // Ensure valid input
        do {
            choice = (char)_getch();
        } while (choice != '1' && choice != '2' && choice != '3');

        system("cls");

        if (choice == '3') {
            break;
        }

        if (choice == '1') {
            problem.processThreads("thread.dat", true);
        } else {
            problem.processThreads("thread.dat", false);
        }

        printf("\nPress Any Key To Continue:");
        _getch();
        system("cls");
    }

    return 0;
}
