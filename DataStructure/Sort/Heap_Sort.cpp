#include<iostream>
#include<vector>
using namespace std;

void printVec(vector<int>& v) {
    for (auto it = v.begin();it != v.end();++it) {
        cout << *it << " ";
    }
    cout << endl;
}

void HeadAdjust(vector<int>& v, int k, int len) {
    v[0] = v[k];//保存需要调整的值
    for (int i = 2 * k;i <= len;i *= 2) {
        if (i < len && v[i] < v[i + 1]) {
            ++i;
        }
        if (v[0] >= v[i]) break;
        else {
            v[k] = v[i];//小元素下坠
            k = i;
        }
    }
    v[k] = v[0];
}

//建立大根堆
void BuildMaxHeap(vector<int>& v, int len) {
    //索引为0不存储数据
    for (int i = len / 2;i > 0;--i) {//依次处理分支节点
        HeadAdjust(v, i, len);
    }
}

void HeapSort(vector<int>& v, int len) {
    BuildMaxHeap(v, len);
    //建立初始堆时间复杂度O(n)
    for (int i = len;i > 1;--i) {
        int tmp = v[i];
        v[i] = v[1];
        v[1] = tmp;
        HeadAdjust(v, 1, i - 1);//剩余元素调整为大根堆
    }
    //时间复杂度O(nlog2n)
}

int main() {
    vector<int> v = { 0,101,100,49,38,65,97,76,13,27,49 };
    printVec(v);
    HeapSort(v,v.size());
    printVec(v);
    return 0;
}