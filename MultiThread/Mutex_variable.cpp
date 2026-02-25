#include<iostream>
#include<string>
#include<windows.h>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;

int a = 0;
double b = 0.0;
mutex mtx;
timed_mutex t_mtx;
void increase() {
    for (int i = 0;i < 10000;++i) {
        //lock_guard<mutex> guard(mtx);
        unique_lock<mutex> ul(mtx);
        ++a;
        b += 0.1;
    }
}

void increase2() {
    unique_lock<timed_mutex> ul(t_mtx);
    if (ul.try_lock_for(chrono::seconds(2))) {
        this_thread::sleep_for(chrono::seconds(3));
        ++a;
    }
}

int main() {
    thread thread1(increase2);
    thread thread2(increase2);
    thread1.join();
    thread2.join();
    cout << a << endl;
    cout << b << endl;
    return 0;
}