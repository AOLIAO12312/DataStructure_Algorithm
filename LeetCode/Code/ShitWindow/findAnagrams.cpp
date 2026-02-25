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

class Solution {
    public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        if (p.size() > s.size()) {
            return res;
        }
        unordered_map<char, int> p_map;
        for (int i = 0;i < p.size();++i) {
            char c = p[i];
            if (p_map.find(c) == p_map.end()) {
                p_map[c] = 0;
            }
            p_map[c]++;
        }
        unordered_map<char, int> s_map;
        for (int j = 0;j < p.size();++j) {
            char c = s[j];
            if (s_map.find(c) == s_map.end()) {
                s_map[c] = 0;
            }
            s_map[c]++;
        }
        if (s_map == p_map) {
            res.push_back(0);
        }
        for (int i = 0;i < s.size() - p.size() + 1;++i) {
            char c_l = s[i], c_r = s[i + p.size()];
            s_map[c_l]--;
            if (s_map[c_l] <= 0) {
                s_map.erase(c_l);
            }
            if (s_map.find(c_r) == s_map.end()) {
                s_map[c_r] = 0;
            }
            s_map[c_r]++;
            if (s_map == p_map) {
                res.push_back(i + 1);
            }
        }
        return res;
    }
};

int main() {
    string s = "cbaebabacd";
    string p = "abc";
    vector<int> res = Solution().findAnagrams(s, p);
    printVec(res);
    return 0;
}