#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_map<char,int> map;

bool compare(const string& a, const string& b){
    int i = 0;
    while(true){
        if(i >= a.size() && i >= b.size()){
            return false;
        }else if(i >= a.size() && i < b.size()){
            return true;
        }else if(i < a.size() && i >= b.size()){
            return false;
        }else{
            if(map[a[i]] > map[b[i]]){
                return true;
            }else if(map[a[i]] < map[b[i]]){
                return false;
            }
            ++i;
        }
    }
}

int main() {
    string rank;
    vector<string> vs;
    int n = 0;
    cin >> rank;
    cin >> n;
    vs.resize(n);
    for(int i = 0;i<n;++i){
        cin >> vs[i];
    }
    for(int i = 0;i<rank.size();++i){
        map[rank[i]] = rank.size() - i;
    }
    sort(vs.begin(), vs.end(), compare);
    for(int i = 0;i<n;++i){
        cout << vs[i] << endl;
    }

}