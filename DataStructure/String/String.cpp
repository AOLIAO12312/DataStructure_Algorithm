#include <iostream>
#include <string>
using namespace std;

size_t Naive_Patter_Matching(const string& str, const string& substr) {
    if (str.size() > substr.size()) {
        const int Length1 = str.size();
        const int Length2 = substr.size();
        for (size_t i = 0;i < Length1 - Length2 + 1;++i) {
            cout << str.substr(i, Length2) << endl;
            if (str.substr(i, Length2) == substr) {
                return i;
            }
        }
        return string::npos;
    } else {
        return string::npos;
    }
}

int main() {
    string str = "iPhone 15 Pro Max aaaaaaaaaaaaab";
    size_t pos1 = Naive_Patter_Matching(str, "aab");
    if (pos1 == string::npos) {
        cout << "Can't find substr" << endl;
    } else {
        cout << "Pos = " << pos1 << endl;
    }

    size_t pos2 = str.find("aab");
    if (pos2 == string::npos) {
        cout << "Can't find substr" << endl;
    } else {
        cout << "Pos = " << pos2 << endl;
    }
    return 0;
}