#include <iostream>
#include <vector>
using namespace std;

void print_vec(const vector<int>& v) {
    // 打印数组
    for (int num : v) {
        cout << num << " ";
    }
    cout << endl;
}

void full_permutation(const vector<int>& arr, vector<bool>& used, vector<int>& current) {
    // 发现数组中的数字被选择完之后打印全排列数组
    if (current.size() == arr.size()) {
        print_vec(current);
        return;
    }
    for (int i = 0; i < arr.size(); ++i) {
        if (!used[i]) {
            // 将该地址标记为已使用状态
            used[i] = true;
            current.push_back(arr[i]);
            // 递归选择数据插入
            full_permutation(arr, used, current);
            // 回溯选择
            current.pop_back();
            used[i] = false;
        }
    }
}

void print_full_permutation(int* arr, int size) {
    vector<int> arr_vec(arr, arr + size);
    vector<bool> used(size, false);
    vector<int> current;
    // 递归生成全排列数组
    full_permutation(arr_vec, used, current);
}

int main() {
    int N;
    cin >> N;
    int* arr = new int[N];
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }
    cout << endl;
    print_full_permutation(arr, N);
    delete[] arr;
    return 0;
}
