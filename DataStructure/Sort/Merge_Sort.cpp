#include<iostream>
#include<vector>
using namespace std;
void printVec(vector<int>& v) {
    for (auto it = v.begin();it != v.end();++it) {
        cout << *it << " ";
    }
    cout << endl;
}

vector<int> Merge(vector<int>& v1, vector<int>& v2) {//假设v1和v2有序
    vector<int> ret;//最终合并的向量
    int i = 0, j = 0, k = 0;
    while (i < v1.size() && j < v2.size()) {
        if (v1[i] <= v2[j]) {
            ret.push_back(v1[i++]);
        } else {
            ret.push_back(v2[j++]);
        }
    }
    while (i < v1.size()) ret.push_back(v1[i++]);
    while (j < v2.size()) ret.push_back(v2[j++]);
    return ret;
}

vector<int> MergeSort(vector<int>& v) {
    vector<int> ret;
    if (v.size() > 1) {
        vector<int> left(v.begin(), v.begin() + v.size() / 2);
        vector<int> right(v.begin() + v.size() / 2, v.end());
        left = MergeSort(left);
        right = MergeSort(right);
        ret = Merge(left, right);
        return ret;
    } else {
        return v;
    }
}

int main() {
    vector<int> v1 = { 7,5,6,42,41,25,2,100,1,3,10,5,21 };
    vector<int> ret = MergeSort(v1);
    printVec(ret);
    return 0;
}