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
int longestConsecutive(vector<int>& nums) {
    unordered_set<int> set;
    int max_cons = 0;
    for (const int& num : nums) {
        set.insert(num);
    }
    for (const int& num : set) {
        if (set.find(num - 1) != set.end()) {
            continue;
        }
        int c_num = num;
        int cons = 0;
        while (set.find(c_num) != set.end()) {
            c_num++;
            cons++;
        }
        if (max_cons < cons) {
            max_cons = cons;
        }
    }
    return max_cons;
}
};

int main() {
    ios::sync_with_stdio(false);
    vector<int> nums = {0,3,7,2,5,8,4,6,0,1};
    int res = Solution().longestConsecutive(nums);
    cout << res << endl;
    return 0;
}