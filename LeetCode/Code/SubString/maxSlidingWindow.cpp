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
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> res(nums.size() - k + 1);
    unordered_map<int, int> map;
    int max = 0x80000000, min = 0x7fffffff;
    for (int i = 0;i < k;++i) {
        if (map.find(nums[i]) == map.end()) {
            map[nums[i]] = 0;
        }
        map[nums[i]]++;
        if (max < nums[i]) {
            max = nums[i];
        }
        if (min > nums[i]) {
            min = nums[i];
        }
    }
    res[0] = max;
    for (int i = 0;i < nums.size() - k;++i) {
        map[nums[i + k]]++;
        if (max < nums[i + k]) {
            max = nums[i + k];
        }
        if (min > nums[i + k]) {
            min = nums[i + k];
        }
        map[nums[i]]--;
        if (map[nums[i]] == 0) {
            if (min == nums[i]) {
                for (int i = min;i <= max;++i) {
                    if (map.find(i) != map.end() && map[i] > 0) {
                        min = i;
                        break;
                    }
                }
            }
            if (max == nums[i]) {
                for (int i = max;i >= min;--i) {
                    if (map.find(i) != map.end() && map[i] > 0) {
                        max = i;
                        break;
                    }
                }
            }
        }
        res[i + 1] = max;
    }
    return res;
}
};

int main() {
    vector<int> nums = {1,-1};
    int k = 1;
    vector<int> res = Solution().maxSlidingWindow(nums, k);
    printVec(res);
    return 0;
}