#include<iostream>
using namespace std;

size_t Fibo(int x) {
    if (x == 1 || x == 0) {
        return 1;
    } else {
        return Fibo(x - 1) + Fibo(x - 2);
    }
}

int main() {
    for (int i = 0;i < 60;++i) {
        cout << "Fibo(" << i << ") = " << Fibo(i) << endl;
    }
    return 0;
}