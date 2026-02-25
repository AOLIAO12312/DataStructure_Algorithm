#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 全局变量
vector<vector<string>> solutions;
vector<string> board;
vector<bool> col, diag1, diag2;

// 回溯函数
void backtrack(int row, int n) {
    if (row == n) {
        solutions.push_back(board); // 找到一个合法解
        return;
    }

    for (int c = 0; c < n; ++c) {
        int d1 = row - c + n - 1; // 主对角线下标
        int d2 = row + c;         // 副对角线下标
        if (col[c] || diag1[d1] || diag2[d2]) continue; // 冲突检测

        // 放置皇后
        board[row][c] = 'Q';
        col[c] = diag1[d1] = diag2[d2] = true;

        backtrack(row + 1, n); // 递归下一行

        // 回溯，撤销皇后
        board[row][c] = '.';
        col[c] = diag1[d1] = diag2[d2] = false;
    }
}

// 主函数入口
int main() {
    int n;
    cin >> n;

    // 初始化全局变量
    board = vector<string>(n, string(n, '.'));
    col = vector<bool>(n, false);
    diag1 = vector<bool>(2 * n - 1, false);
    diag2 = vector<bool>(2 * n - 1, false);
    solutions.clear();

    backtrack(0, n);

    // 输出所有解
    for (const auto& solution : solutions) {
        for (const string& row : solution) {
            cout << row << endl;
        }
        cout << endl;
    }

    return 0;
}
