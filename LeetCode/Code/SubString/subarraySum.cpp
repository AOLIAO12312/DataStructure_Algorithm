#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
int subarraySum(vector<int>& nums, int k) {
    int res = 0;
    int n = nums.size();
    vector<int> sum(n + 1);
    sum[0] = 0;
    for (int i = 0;i < n;++i) {
        sum[i + 1] = sum[i] + nums[i];
    }
    for (int i = 0;i < n;++i) {
        for (int j = i + 1;j <= n;++j) {
            if (sum[j] - sum[i] == k) {
                ++res;
            }
        }
    }
    return res;
}
};

int main() {
    vector<int> nums = {6,4,3,1};
    int k = 10;
    int res = Solution().subarraySum(nums, k);
    cout << res << endl;
    return 0;
}