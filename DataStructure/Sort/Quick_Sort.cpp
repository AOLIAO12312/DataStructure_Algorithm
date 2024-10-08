#include<iostream>
#include<vector>
using namespace std;

void printVec(vector<int>& v) {
    for (auto it = v.begin();it != v.end();++it) {
        cout << *it << " ";
    }
    cout << endl;
}

int Partition(vector<int>& v, int low, int high) {
    int pivot = v[low];//基准
    //根据“基准”将源表划分为左右两个部分
    while (low < high) {
        while (low < high && v[high] >= pivot) --high;
        v[low] = v[high];
        while (low < high && v[low] <= pivot) ++low;
        v[high] = v[low];
    }
    v[low] = pivot;
    return low;//也可以随机选取枢轴元素
}

void QuickSort(vector<int>& v, int low, int high) {//递归调用
    //最好时间复杂度O(nlog2n)
    //最坏O(n^2)
    //不稳定排序
    if (low < high) {
        int pivotpos = Partition(v, low, high);
        QuickSort(v, low, pivotpos - 1);
        QuickSort(v, pivotpos + 1, high);
    }
}

int main() {
    vector<int> v = { 101,49,38,65,100,97,76,13,27,49 };
    printVec(v);
    QuickSort(v, 0, v.size() - 1);
    printVec(v);
    return 0;
}