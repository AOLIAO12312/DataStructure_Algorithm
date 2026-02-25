#include<string>
#include<algorithm>
#include<iostream>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    string res;
    char a_char = 'a', b_char = 'b';
    if (a < b) {
        swap(a, b);
        swap(a_char, b_char);
    }

    while (a > 0 || b > 0) {
        if (a > 0) {        // 添加一个较多的字符
            res.push_back(a_char);
            a--;
        }
        if (a > b) {        // 若仍较多，再添加一个
            res.push_back(a_char);
            a--;
        }
        if (b > 0) {        // 添加另一个字符
            res.push_back(b_char);
            b--;
        }
    }
    cout << res << endl;
    return 0;
}