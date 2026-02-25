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

void printVecS(const vector<vector<string>>& res) {
    for (int i = 0;i < res.size();++i) {
        printVec(res[i]);
    }
}

class Solution {
    public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        unordered_map<string, vector<int>> map;
        for (int i = 0;i < strs.size();++i) {
            string str = strs[i];
            sort(str.begin(), str.end());
            if (map.find(str) == map.end()) {
                map[str] = vector<int>({});
            }
            map[str].push_back(i);
        }
        for (const auto& pair : map) {
            vector<int> vec = pair.second;
            vector<string> vs;
            for (int i = 0;i < vec.size();++i) {
                vs.push_back(strs[vec[i]]);
            }
            res.push_back(vs);
        }
        return res;
    };
};

int main() {
    ios::sync_with_stdio(false);
    vector<string> strs = {""};
    vector<vector<string>> res = Solution().groupAnagrams(strs);
    printVecS(res);
    return 0;
}