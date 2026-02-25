#include<iostream>
using namespace std;

int main() {
    int a = 0x80000000;
    cout << "a = " << a << endl;
    if (a == -a) {
        cout << "a == -a" << endl;
    } else {
        cout << "a != -a" << endl;
    }
    return 0;
}