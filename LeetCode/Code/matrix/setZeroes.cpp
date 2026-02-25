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
void setZeroes(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();
    vector<pair<int, int>> v_pair;
    for (int i = 0;i < m;++i) {
        vector<int> rol = matrix[i];
        for (int j = 0;j < n;++j) {
            if (rol[j] == 0) {
                v_pair.push_back(pair<int, int>(i, j));
            }
        }
    }
    for (int i = 0;i < v_pair.size();++i) {
        int row = v_pair[i].first, col = v_pair[i].second;
        for (int j = 0;j < n;++j) {
            matrix[row][j] = 0;
        }
        for (int j = 0;j < m;++j) {
            matrix[j][col] = 0;
        }
    }
}
};

int main() {
    vector<vector<int>> matrix = { {1,1,1},{1,0,1},{1,1,1} };
    Solution().setZeroes(matrix);
    printVecVec(matrix);
    return 0;
}