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
    int maxArea(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int max_area = 0;
        int area = 0;
        while (left < right) {
            area = min(height[left], height[right]) * (right - left);
            if (max_area < area) {
                max_area = area;
            }
            if (height[left] > height[right]) {
                right--;
            } else {
                left++;
            }
        }
        return max_area;
    }
};

int main() {
    ios::sync_with_stdio(false);
    vector<int> height = {1,8,6,2,5,4,8,3,7};
    int res = Solution().maxArea(height);
    cout << res << endl;
    return 0;
}
