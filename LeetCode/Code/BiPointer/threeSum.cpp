#include<bits/stdc++.h>
using namespace std;
template <class T>
void printVec(const vector<T>& vec) {
    cout << "[";
    for (int i = 0;i < vec.size();++i) {
        if (i == vec.size() - 1) {
            cout << vec[i];
        } else {
            cout << vec[i] << ",";
        }
    }
    cout << "]" << endl;
}

void printVecVec(const vector<vector<int>>& vec) {
    for (auto v : vec) {
        printVec(v);
    }
}

class Solution {
    public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.size() < 3) {
            return res;
        }
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 0;i < n - 2;++i) {
            while (i > 0 && nums[i] == nums[i - 1] && i < n - 2) ++i;
            int l = i + 1, r = n - 1;
            int target = -nums[i];
            while (l < r) {
                while (l > i + 1 && nums[l] == nums[l - 1] && l < r) ++l;
                while (r < n - 1 && nums[r] == nums[r + 1] && l < r) --r;
                if (l >= r) break;
                if (nums[l] + nums[r] == target) {
                    res.push_back(vector<int>({ nums[i],nums[l],nums[r] }));
                    ++l;
                    --r;
                    continue;
                }
                if (nums[l] + nums[r] > target) {
                    --r;
                } else {
                    ++l;
                }
            }
        }
        return res;
    }
};

int main() {
    vector<int> nums = {-1,0,1,2,-1,-4};
    vector<vector<int>> res = Solution().threeSum(nums);
    printVecVec(res);
    return 0;
}