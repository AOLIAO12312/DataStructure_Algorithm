#include<bits/stdc++.h>
using namespace std;

class Solution {
    public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return nums[0];
        }
        vector<int> sums(n + 1);
        int res = INT_MIN;
        int min = INT_MAX, max = INT_MIN;
        sums[0] = 0;
        for (int i = 0;i < n;++i) {
            sums[i + 1] = sums[i] + nums[i];
        }
        for (int i = 0;i < n;++i) {
            if (min > sums[i]) {
                min = sums[i];
                max = sums[i + 1];
            }
            if (max < sums[i + 1]) {
                max = sums[i + 1];
            }
            if (res < max - min) {
                res = max - min;
            }
        }
        return res;
    }
};

int main() {
    vector<int> nums = {-2,1};
    int res = Solution().maxSubArray(nums);
    cout << res << endl;
    return 0;
}