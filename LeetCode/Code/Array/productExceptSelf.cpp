#include<bits/stdc++.h>
using namespace std;
template<class T>
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
    for (vector<int> item : vec) {
        printVec(item);
    }
    cout << endl;
}

class Solution {
public:
vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> res(n);
    
}
};

int main() {
    vector<int> nums = {-1,2};
    vector<int> res = Solution().productExceptSelf(nums);
    printVec(res);
    return 0;
}