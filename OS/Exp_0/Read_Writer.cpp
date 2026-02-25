#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <string>

using namespace std;

// ========== Semaphore Implementation ==========
class Semaphore {
private:
    mutex mtx;
    condition_variable cv;
    int count;
public:
    Semaphore(int count_ = 0) : count(count_) {}

    void wait() {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [&](){ return count > 0; }); // wait until count > 0
        count--;
    }

    void signal() {
        unique_lock<mutex> lock(mtx);
        count++;
        cv.notify_one(); // wake up a thread waiting for the signal
    }
};

// ========== Shared Variables and Semaphores ==========
int readCount = 0;
int writeCount = 0;

Semaphore mutexRead(1);    // Protect readCount
Semaphore mutexWrite(1);   // Protect writeCount
Semaphore resource(1);     // Controls access to the shared resource
Semaphore readTry(1);      // Blocks readers when writers are waiting

// ========== Simulated Shared Resource Access ==========
void access_shared_data(const string& thread_name, const string& operation, int duration = 1000) {
    cout << thread_name << " starts " << operation << " operation." << endl;
    this_thread::sleep_for(chrono::milliseconds(duration));
    cout << thread_name << " ends " << operation << " operation." << endl;
}

// ========== Reader-Preference Reader ==========
void reader_reader_priority(int id) {
    string name = "Reader-" + to_string(id);
    cout << name << " created." << endl;
    this_thread::sleep_for(chrono::milliseconds(100));

    cout << name << " requests to read." << endl;
    mutexRead.wait();
    readCount++;
    if (readCount == 1) {
        resource.wait();
    }
    mutexRead.signal();

    access_shared_data(name, "read");

    mutexRead.wait();
    readCount--;
    if (readCount == 0) {
        resource.signal();
    }
    mutexRead.signal();
}

// ========== Writer-Preference Reader ==========
void reader_writer_priority(int id) {
    string name = "Reader-" + to_string(id);
    cout << name << " created." << endl;
    this_thread::sleep_for(chrono::milliseconds(100));

    cout << name << " requests to read." << endl;
    readTry.wait();
    mutexRead.wait();
    readCount++;
    if (readCount == 1) {
        resource.wait();
    }
    mutexRead.signal();
    readTry.signal();

    access_shared_data(name, "read");

    mutexRead.wait();
    readCount--;
    if (readCount == 0) {
        resource.signal();
    }
    mutexRead.signal();
}

// ========== Reader-Preference Writer ==========
void writer_reader_priority(int id) {
    string name = "Writer-" + to_string(id);
    cout << name << " created." << endl;
    this_thread::sleep_for(chrono::milliseconds(100));

    cout << name << " requests to write." << endl;
    mutexWrite.wait();
    resource.wait();

    access_shared_data(name, "write");

    resource.signal();
    mutexWrite.signal();
}

// ========== Writer-Preference Writer ==========
void writer_writer_priority(int id) {
    string name = "Writer-" + to_string(id);
    cout << name << " created." << endl;
    this_thread::sleep_for(chrono::milliseconds(100));

    cout << name << " requests to write." << endl;
    mutexWrite.wait();
    writeCount++;
    if (writeCount == 1) {
        readTry.wait();
    }
    mutexWrite.signal();

    resource.wait();

    access_shared_data(name, "write");

    resource.signal();

    mutexWrite.wait();
    writeCount--;
    if (writeCount == 0) {
        readTry.signal();
    }
    mutexWrite.signal();
}

// ========== Main Function ==========
int main() {
    const int n = 6;
    vector<thread> threads;

    // Reader Priority Test
    cout << "======== Reader Preference Test ========" << endl;
    for (int i = 0; i < n; ++i) {
        if (i % 3 == 0)
            threads.emplace_back(writer_reader_priority, i);
        else
            threads.emplace_back(reader_reader_priority, i);
    }
    for (auto &t : threads) t.join();

    threads.clear();
    readCount = 0;

    // Writer Priority Test
    cout << "\n======== Writer Preference Test ========" << endl;
    for (int i = 0; i < n; ++i) {
        if (i % 3 == 0)
            threads.emplace_back(writer_writer_priority, i);
        else
            threads.emplace_back(reader_writer_priority, i);
    }
    for (auto &t : threads) t.join();

    return 0;
}
