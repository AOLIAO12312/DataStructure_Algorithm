#include<iostream>
#include<string>
using namespace std;

//朴素的字符串配对算法
size_t FindSubStr(const string& str, const string& subStr) {
    size_t i = 0, j = 0;
    while (i < str.length() && j < subStr.length()) {
        if (str.at(i) == subStr.at(j)) {
            ++i, ++j;
        } else {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j >= subStr.length()) {
        return i - subStr.length();
    } else {
        return string::npos;
    }
}

//求next数组
size_t* getNext(const string& subStr) {
    size_t* next = new size_t[subStr.length()];
    size_t i = 0, j = -1;
    next[0] = -1;

    // i ~ j-1个字符组成的串记为S
    //next[j] = S的最长相等前后缀长度
    while (i < subStr.length() - 1) {
        if (j == -1 || subStr.at(i) == subStr.at(j)) {
            ++i, ++j;
            next[i] = j;
        } else {
            j = next[j];
        }
    }

    size_t* nextval = new size_t[subStr.length()];//优化next数组为nextval数组
    //使之执行效率更高
    nextval[0] = -1;
    for (int k = 1;k < subStr.length();++k) {
        if (subStr.at(next[k]) == subStr.at(k)) {
            nextval[k] = nextval[next[k]];
        } else {
            nextval[k] = next[k];
        }
    }
    
    // for (int k = 0;k < subStr.length();++k) {
    //     cout << nextval[k] << " ";
    // }
    // cout << endl;
    delete[] next;//释放next数组的内存
    return nextval;
}

//KMP算法配对字符串
//i不回溯
size_t index_KMP(const string& str, const string& subStr) {
    size_t i = 0, j = 0;
    size_t* next = getNext(subStr);
    while (i < str.length() && j < subStr.length() || j == -1) {
        if (j == -1 || str.at(i) == subStr.at(j)) {
            ++i, ++j;
        } else {
            j = next[j];
        }
    }
    delete[] next;
    if (j >= subStr.length()) {
        return i - subStr.length();//返回指定字符串的位置
    } else {
        return string::npos;
    }
}

int main() {
    string str = "iPhoneannafbabaaaabaa";
    //cout << FindSubStr(str, "one") << endl;
    cout << index_KMP(str, "aaaab") << endl;
    return 0;
}