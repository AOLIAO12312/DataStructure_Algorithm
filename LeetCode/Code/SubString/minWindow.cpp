#include<bits/stdc++.h>
using namespace std;

class Solution {
    public:
    bool check(const unordered_map<char, int>& map_s,const unordered_map<char,int>& map_t) {
        for (const auto& pair : map_t) {
            auto it = map_s.find(pair.first);
            if (it == map_s.end()) {
                return false;
            }
            if (it->second < pair.second) {
                return false;
            }
        }
        return true;
    }

    string minWindow(string s, string t) {
    int m = s.size(), n = t.size();
    if (m < n) {
        return "";
    }

    unordered_map<char, int> map_t;
    for (int i = 0; i < n; ++i) {
        map_t[t[i]]++;
    }

    int l = 0, r = 0;  // 修改：从 0 开始，更通用，后面会调整
    int min_len = INT_MAX, min_l = -1, min_r = -1;

    unordered_map<char, int> map_s;

    // 新增：valid 表示当前有多少个字符已经满足数量要求
    int valid = 0;
    // 新增：记录当前窗口中每个字符是否已经满足 map_t 中的要求
    for (const auto& p : map_t) {
        char c = p.first;
        if (map_s[c] == p.second) valid++;  // 错误！此时 map_s 还没填充
    }

    // 正确的方式是：我们需要跟踪对于每个在 map_t 中的字符，map_s 中的 count 是否 >= map_t 中的 count
    // 所以我们用一个单独的 valid 计数，动态维护

    // 因此，我们重新设计：
    valid = 0;
    for (const auto& p : map_t) {
        // 只是初始化，valid 还是 0
    }

    // 正确的逻辑是：在滑动窗口过程中，每当我们添加/移除一个字符 c，
    // 如果 c 在 map_t 中，且 map_s[c] 的数量刚刚达到 map_t[c]，则 valid++
    // 如果 map_s[c] 的数量刚刚小于 map_t[c]，则 valid--

    // 所以我们初始化 valid = 0;
    valid = 0;

    // 重新初始化 map_s 和窗口
    map_s.clear();
    l = 0;
    r = 0;

    // 先初始化窗口为前 n 个字符？你原代码这么做的，但我们现在改成通用滑动窗口
    // 【改动点】我们不再一开始只搞前n个字符，而是从 l=0, r=0 开始滑动窗口，更通用且高效

    for (; r < m; ++r) {
        char c = s[r];
        if (map_t.count(c)) {  // 当前字符是 t 中需要的
            map_s[c]++;
            if (map_s[c] == map_t[c]) {  // 刚好满足需求
                valid++;
            }
        }

        // 当窗口已经满足所有字符需求时
        while (valid == map_t.size() && l <= r) {
            // 更新最小窗口
            int len = r - l + 1;
            if (len < min_len) {
                min_len = len;
                min_l = l;
                min_r = r;
            }

            // 尝试缩小左边界
            char left_char = s[l];
            if (map_t.count(left_char)) {
                if (map_s[left_char] == map_t[left_char]) {
                    valid--;  // 刚好不满足了
                }
                map_s[left_char]--;
            }
            l++;
        }
    }

    if (min_l == -1) {
        return "";
    }
    return s.substr(min_l, min_r - min_l + 1);
}
};

int main() {
    string s = "ADOBECODEBANC";
    string t = "ABC";
    string res = Solution().minWindow(s, t);
    cout << res << endl;
    return 0;
}