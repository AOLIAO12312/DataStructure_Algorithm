#include<iostream>
#include<string>
#include<vector>
using namespace std;

void print_vec(const vector<int>& v) {
    // 打印数组
    for (int num : v) cout << num << " ";
    cout << endl;
}

int main() {
    string s;
    cin >> s;
    vector<int> v;
    int left_bound = 0, right_bound = s.size();

    while (left_bound != s.size()) {
        int left = left_bound, right = s.size() - 1;
        right_bound = s.size();

        //贪心算法开始
        // 寻找一个最小的片段，包含当前起始位置出现的所有字符的最后一次出现
        while (left < right_bound) {
            char c = s[left];
            while (s[right] != c) right--;
            // 更新当前片段的右边界，确保包含所有字符的最后一次出现
            if ((right > right_bound) || (right_bound == s.size())) right_bound = right;
            left++;
            right = s.size() - 1;
        }
        //贪心算法结束

        v.push_back(right_bound - left_bound + 1);
        left_bound = right_bound + 1;
    }

    print_vec(v);
    return 0;
}
