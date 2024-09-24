#include<iostream>
#include<vector>
using namespace std;

//希尔排序

void printVec(vector<int>& v) {
    for (auto it = v.begin();it != v.end();++it) {
        cout << *it << " ";
    }
    cout << endl;
}

void ShellSort(vector<int>& v) {//从索引为1的数据进行排序
    int d, i, j;
    for (d = v.size() / 2;d >= 1;d /= 2) {
        for (i = d + 1;i <= v.size();++i) {
            if(v[i] < v[i-d]){
                v[0] = v[i];
                for(j = i-d;j>0 && v[0] < v[j];j-=d){
                    v[j + d] = v[j];
                }
                v[j + d] = v[0];
            }//if
        }
    }
}

int main() {//v[0]不存储有效数据
    vector<int> v = { 0,49,13,27,97,76,38,65,49 };
    ShellSort(v);
    printVec(v);
    return 0;
}