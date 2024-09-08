#include<iostream>
using namespace std;

int Binary_Search(int* arr,int size,int target) {
    int low = 0;
    int high = size - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] > target) {
            high = mid - 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        }
    }
    return -1;
}

int main() {
    int arr[10];
    for (int i = 0;i < 10;++i) {
        arr[i] = i;
    }
    cout << Binary_Search(arr, 10, 4) << endl;;

    return 0;
}