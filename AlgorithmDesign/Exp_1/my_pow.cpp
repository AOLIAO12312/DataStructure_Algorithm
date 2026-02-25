#include<iostream>
using namespace std;


double my_pow_positive(double x, int n) {
    if (n == 0) {//中止条件n = 0
        return 1;
    } else if (n == 1) {//中止条件n = 1
        return x;
    } else {
        //采用分治策略
        if (n % 2 == 0) {
            //若n为偶数则直接返回n/2次幂的平方
            return my_pow_positive(x, n / 2) * my_pow_positive(x, n / 2);//递归
        } else {
            //若为奇数则返回n/2次幂的平方再乘以x
            return my_pow_positive(x, n / 2) * my_pow_positive(x, n / 2) * x;//递归
        }
    }
}

double my_pow(double x, int n) {
    //对n的正负性进行处理
    if (n < 0) {
        //为负直接返回整数n次方的倒数
        return 1 / my_pow_positive(x, -n);
    } else {
        //为正就直接计算n次方
        return my_pow_positive(x, n);
    }
}


int main() {
    double x;
    int n;
    cout << "x = ";
    cin >> x;
    cout << "n = ";
    cin >> n;

    cout << "x^n = " << my_pow(x, n) << endl;

    return 0;
}