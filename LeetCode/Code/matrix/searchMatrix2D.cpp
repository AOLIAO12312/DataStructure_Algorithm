#include<iostream>
#include<vector>
using namespace std;

class Solution0 { // 暴力解法 O(m*n)
public:
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    for (int i = 0;i < matrix.size();++i) {
        for (int j = 0;j < matrix[0].size();++j) {
            if (matrix[i][j] == target) {
                return true;
            }
        }
    }
}
};

class Solution { // 二分查找 O(m*log(n))
    public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        int i = 0, j = n - 1;
        while (i < m && j >= 0) {
            if (matrix[i][j] == target) {
                return true;
            } else if (matrix[i][j] > target) {
                --j;
            } else {
                ++i;
            }
        }
        return false;
    }
};
int main() {
    vector<vector<int>> matrix = { {1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30} };
    int target = 29;
    Solution sol;
    bool result = sol.searchMatrix(matrix, target);
    cout << "Result: " << result << endl;
}