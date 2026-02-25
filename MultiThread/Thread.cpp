#include<iostream>
#include<string>
#include<windows.h>
#include<thread>
using namespace std;

void print(string s) {
    for (int i = 0;i < 10;++i) {
        cout << s << ": " << i << endl;
        Sleep(1000);
    }
}

int main() {
    thread thread1(print, "A");
    Sleep(100);
    thread thread2(print, "B");
    thread1.join();
    thread2.detach();
    return 0;
}