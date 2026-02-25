#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int lengthOfLIS(vector<int>& nums) {
    if (nums.empty()) return 0;
    vector<int> dp(nums.size(), 1);
    int maxLength = 1;

    for (int i = 1; i < nums.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[j] < nums[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        maxLength = max(maxLength, dp[i]);
    }

    return maxLength;
}

int main() {
    vector<int> nums1 = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "example 1 input:";
    for(auto num : nums1) cout << num << " ";
    cout << "\nexaxple 1 output:" << lengthOfLIS(nums1) << endl;
    cout << endl;

    vector<int> nums2 = {0, 1, 0, 3, 2, 3};
    cout << "example 2 input:";
    for(auto num : nums2) cout << num << " ";
    cout << "\nexaxple 2 output:" << lengthOfLIS(nums2) << endl;
    cout << endl;

    vector<int> nums3 = {7, 7, 7, 7, 7, 7, 7};
    cout << "example 3 input:";
    for(auto num : nums3) cout << num << " ";
    cout << "\nexaxple 3 output:" << lengthOfLIS(nums3) << endl;
    cout << endl;

    vector<int> nums4 = {1, 3, 6, 7, 9, 4, 10, 5, 6};
    cout << "example 4 input:";
    for(auto num : nums4) cout << num << " ";
    cout << "\nexaxple 4 output:" << lengthOfLIS(nums4) << endl;

    return 0;
}