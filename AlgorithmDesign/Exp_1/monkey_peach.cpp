#include<iostream>
using namespace std;

size_t remain_peach(size_t peach, int days) {
    if (days == 1) {//
        //中止条件：如果最后只剩下最后一天则直接返回peach个数
        return peach;
    } else {
        //如果多于一天则向下递归计算之前天数的桃子数目
        return remain_peach((peach + 1) * 2, days - 1);
    }
}

int main() {
    int days;
    cout << "days = ";
    cin >> days;
    cout << "peach = " << remain_peach(1, days) << endl;
    return 0;
}