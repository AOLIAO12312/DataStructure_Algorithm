#include<iostream>
#include<vector>
using namespace std;

void printVec(vector<int>& v) {
    for (auto it = v.begin();it != v.end();++it) {
        cout << *it << " ";
    }
    cout << endl;
}

void insertSort(vector<int>& v) {//可以优化为折半插入排序 减少遍历次数
    for (int i = 1;i < v.size();++i) {
        if (v[i] < v[i - 1]) {
            int tmp = v[i];
            for (int j = i - 1;j >= 0;--j) {
                v[j + 1] = v[j];
                if (tmp >= v[j - 1] || j == 0) {
                    v[j] = tmp;
                    break;
                }
            }
        }
    }
}

void insertSortBin(vector<int>& v) {//折半插入排序
    int i, j, low, high, mid;
    for (i = 2;i <= v.size();++i) {
        v[0] = v[i];
        low = 1;high = i - 1;
        while (low <= high) {
            mid = (low + high) / 2;
            if (v[mid] > v[0]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        for (j = i - 1;j >= high + 1;--j) {
            v[j + i] = v[j];
        }
        v[high + 1] = v[0];
    }
}

void bubbleSort(vector<int>& v) {//冒泡排序
    for (int i = 0;i < v.size();++i) {
        bool flag = false;
        for (int j = 0;j < v.size() - i - 1;++j) {
            if (v[j] > v[j + 1]) {
                int tmp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = tmp;
                flag = true;
            }
        }
        if (flag == false) {//如果没有进行交换则表明该序列已经有序
            return;
        }
    }
}

int main() {
    vector<int> v = { 101,100,49,38,65,97,76,13,27,49 };
    printVec(v);
    //insertSortBin(v);
    bubbleSort(v);
    printVec(v);
}