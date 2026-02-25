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
    enum { RIGHT, DOWN, LEFT, UP };
    bool is_valid(pair<int, int> pos, vector<vector<int>>& matrix, int m, int n) {
        if (pos.first >= 0 && pos.first < m && pos.second >= 0 && pos.second < n) {
            if (matrix[pos.first][pos.second] != INT_MIN) {
                return true;
            }
        }
        return false;
    }
    pair<int, int> next_step(const pair<int, int> pos, int& direction, vector<vector<int>>& matrix,const int& m,const int& n) {
        pair<int, int> new_pos = pos;
        int i = 0;
        while (i < 4) {
            switch (direction) {
                case RIGHT:
                    new_pos.second++;
                    break;
                case DOWN:
                    new_pos.first++;
                    break;
                case LEFT:
                    new_pos.second--;
                    break;
                case UP:
                    new_pos.first--;
                    break;
                default:
                    assert(true);
                    break;
                }
            if (is_valid(new_pos, matrix, m, n)) {
                return new_pos;
            } else {
                direction = (direction + 1) % 4;
                new_pos = pos;
            }
            ++i;
        }
        return pair<int, int>(-1, -1);
    }
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        int m = matrix.size(), n = matrix[0].size();
        int direction = RIGHT;
        pair<int, int> pos(0, 0);
        while (true) {
            res.push_back(matrix[pos.first][pos.second]);
            matrix[pos.first][pos.second] = INT_MIN;
            pos = next_step(pos, direction, matrix, m, n);
            if (!is_valid(pos,matrix,m,n)) {
                break;
            }
        }
        return res;
    }
};

int main() {
    vector<vector<int>> matrix = {{1,2,3,4},{4,5,6,7},{7,8,9,10}};
    vector<int> res = Solution().spiralOrder(matrix);
    printVec(res);
    return 0;
}