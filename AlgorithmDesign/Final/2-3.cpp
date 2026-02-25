#include<iostream>
using namespace std;

int main() {
    int N;
    cin >> N;
    // 输入每家的钱财
    int* arr = new int[N];
    // 定义动态dp数组
    int* dp = new int[N];
    for (int i = 0;i < N;++i) {
        cin >> arr[i];
    }

    // 特殊情况讨论
    if (N == 0) {
        cout << 0 << endl;
        return 0;
    }
    if (N == 1) {
        cout << arr[0] << endl;
        return 0;
    }
    if (N == 2) {
        cout << max(arr[0], arr[1]) << endl;
        return 0;
    }


    dp[0] = arr[0];
    dp[1] = arr[1];
    dp[2] = arr[0] + arr[2];

    for (int i = 3;i < N;++i) {
        // 动态规划选择最大的数值
        dp[i] = max(dp[i - 2], dp[i - 3]) + arr[i];
    }

    cout << max(dp[N - 1], dp[N - 2]) << endl;

    delete[] arr;
    delete[] dp;
    return 0;
}