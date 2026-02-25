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


class Solution {
public:
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> map;
    for (int i = 0;i < nums.size();++i) {
        if (map.find(nums[i]) != map.end()) {
            return vector<int>({ map[nums[i]],i });
        } else {
            map[target - nums[i]] = i;
        }
    }
    return vector<int>({ -1,-1 });
    }
};



int main() {
    ios::sync_with_stdio(false);
    vector<int> nums = { 2,7,11,15 };
    int target = 22;
    vector<int> result = Solution().twoSum(nums, target);
    printVec(result);
    return 0;
}