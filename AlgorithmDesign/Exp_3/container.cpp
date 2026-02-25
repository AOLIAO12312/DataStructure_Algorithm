#include<iostream>
using namespace std;

int main() {
    int n;
    int arr[10001];
    cin >> n;
    for (int i = 0;i < n;++i) {
        cin >> arr[i];
    }
    int left = 0, right = n - 1;
    int max_size = min(arr[left], arr[right]) * (right - left);//初始状态容量
    int max_left = 0, max_right = n - 1;
    while (left < right) {
        if (arr[left] < arr[right]) {//定义左右指针寻找最大容量
            ++left;
            if (arr[left] > max_left && min(arr[left], arr[right]) * (right - left) > max_size) {//当该指针指向的值比上一个大且容器容量更大时进行更新
                max_size = min(arr[left], arr[right]) * (right - left);
                max_left = arr[left];
            }
        } else {
            --right;
            if (arr[right] > max_right && min(arr[left], arr[right]) * (right - left) > max_size) {
                max_size = min(arr[left], arr[right]) * (right - left);
                max_right = arr[right];
            }
        }
    }
    cout << max_size << endl;
    return 0;
}