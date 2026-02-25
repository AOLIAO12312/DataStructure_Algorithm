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
    for (vector<int> item : vec) {
        printVec(item);
    }
    cout << endl;
}

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int i = 0, j = 0;
        int dis = abs(target - matrix[i][j]);
        while (dis != 0) {
            if (target > matrix[i][j]) {
                if (i == m - 1 && j == n - 1) {
                    return false;
                }
                else if (i == m - 1) {
                    j++;
                } else if (j == n - 1) {
                    i++;
                }else {
                    if (abs(target - matrix[i + 1][j]) <= abs(target - matrix[i][j + 1])) {
                        i++;
                    } else {
                        j++;
                    }
                }
            } else {
                if (i == 0 && j == 0) {
                    return false;
                }
                else if (i == 0) {
                    j--;
                } else if (j == 0) {
                    i--;
                }else {
                    if (abs(target - matrix[i - 1][j]) <= abs(target - matrix[i][j - 1])) {
                        i--;
                    } else {
                        j--;
                    }
                }
            }
            if (dis >= abs(target - matrix[i][j])) {
                dis = abs(target - matrix[i][j]);
            } else {
                return false;
            }
        }
        return true;
    }
};

int main() {
    vector<vector<int>> matrix = { {1, 4, 7, 11, 15},{2, 5, 8, 12, 19},{3, 6, 9, 16, 22},{10, 13, 14, 17, 24},{18, 21, 23, 26, 30}};
    bool res = Solution().searchMatrix(matrix,17);
    cout << res << endl;
    return 0;
}