#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 获取最大值
int getMax(const vector<int>& arr) {
    return *max_element(arr.begin(), arr.end());
}

// 计数排序，用于基数排序的子过程
void countingSort(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);  // 输出数组
    int count[10] = {0};    // 计数数组

    // 根据当前位数进行计数
    for (int i = 0; i < n; i++) {
        int index = (arr[i] / exp) % 10;
        count[index]++;
    }

    // 更新计数数组，使其储存位置索引
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // 根据计数数组，将当前位的元素放入输出数组
    for (int i = n - 1; i >= 0; i--) {
        int index = (arr[i] / exp) % 10;
        output[count[index] - 1] = arr[i];
        count[index]--;
    }

    // 将排序后的结果拷贝回原数组
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// 基数排序主函数
void radixSort(vector<int>& arr) {
    int maxVal = getMax(arr);

    // 从最低位开始排序，直到最大数的最高位
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSort(arr, exp);
    }
}

int main() {
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
    
    cout << "Unsort: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    radixSort(arr);

    cout << "Sort: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
