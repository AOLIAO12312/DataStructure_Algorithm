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

// class Solution {
// public:
//     void rotate(vector<vector<int>>& matrix) {
//         int n = matrix.size();
//         bool arr[n][n] = { false };
//         for (int i = 0;i < n;++i) {
//             for (int j = 0;j < n;++j) {
//                 arr[i][j] = false;
//             }
//         }
//         for (int i = 0;i < n;++i) {
//             for (int j = 0;j < n;++j) {
//                 if (arr[i][j] == false) {
//                     int tmp = matrix[i][j];
//                     int x = i, y = j;
//                     swap(x, y);
//                     y = n - y - 1;
//                     do {
//                         swap(tmp, matrix[x][y]);
//                         arr[x][y] = true;
//                         swap(x, y);
//                         y = n - y - 1;
//                     } while (arr[x][y] == false);
//                 }
//             }
//         }
//     }
// };

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();

        // 1. 转置矩阵 (i < j)
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }

        // 2. 每一行进行反转
        for (int i = 0; i < n; ++i) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};

int main() {
    vector<vector<int>> matrix = { {5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16} };
    Solution().rotate(matrix);
    printVecVec(matrix);
    return 0;
}