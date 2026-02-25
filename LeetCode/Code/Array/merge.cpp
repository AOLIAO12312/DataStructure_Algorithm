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
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> res;
        if (intervals.size() == 1) {
            return intervals;
        }
        sort(intervals.begin(), intervals.end(), [](const vector<int>& v1, const vector<int>& v2) {
            return v1[0] < v2[0];
            });
        int left = intervals[0][0], right = intervals[0][1];
        for (int i = 1;i < intervals.size();++i) {
            if (intervals[i][0] <= right) {
                if(intervals[i][1] > right)
                    right = intervals[i][1];
            } else {
                res.push_back(vector<int> {left, right});
                left = intervals[i][0];
                right = intervals[i][1];
            }
            if (i == intervals.size() - 1) {
                res.push_back(vector<int> {left, right});
                break;
            }
        }
        return res;
    }
};



int main() {
    vector<vector<int>> intervals = { { 1,4 }, { -1,3} };
    vector<vector<int>> res = Solution().merge(intervals);
    printVecVec(intervals);
    printVecVec(res);
    return 0;
}