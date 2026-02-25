#include<bits/stdc++.h>
using namespace std;
template<class T>
void printVec(const vector<T>& vec) {
    cout << "[";
    for (T item : vec) {
        cout << item << " ";
    }
    cout << "]";
}

void printVecVec(const vector<vector<int>>& vec) {
    for (vector<int> item : vec) {
        printVec(item);
    }
    cout << endl;
}

class Solution {
    public:
    void reverse(vector<int>& nums, int begin, int end) {
        while (begin < end) {
            swap(nums[begin], nums[end]);
            begin++;
            end--;
        }

    }
    void rotate(vector<int>& nums, int k) {
        k %= nums.size();
        reverse(nums, 0, nums.size() - 1);
        reverse(nums, 0, k - 1);
        reverse(nums, k, nums.size() - 1);
    }
};

int main() {
    vector<int> nums = {1,2,3,4,5,6,7};
    int k = 3;
    Solution().rotate(nums,k);
    printVec(nums);
    return 0;
}