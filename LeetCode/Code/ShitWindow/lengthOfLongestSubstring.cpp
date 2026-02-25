#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int l = 0, r = 0;
        int res = 0;
        unordered_map<char, int> map;
        for (r = 0;r < s.size();++r) {
            char c = s[r];
            if (map.find(c) == map.end()) {
                map[c] = 1;
            } else {
                map[c]++;
            }
            if (map[c] > 1) {
                while (l < r) {
                    map[s[l]]--;
                    ++l;
                    if(c == s[l - 1]) break;
                }
            }

            
            if (res < r - l + 1) {
                res = r - l + 1;
            }
        }
        return res;
    }
};

int main() {
    string s = " ";
    int res = Solution().lengthOfLongestSubstring(s);
    cout << res << endl;
    return 0;
}