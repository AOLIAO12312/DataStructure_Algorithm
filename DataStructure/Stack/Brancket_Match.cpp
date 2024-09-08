#include<iostream>
#include<stack>
using namespace std;

int main(){
    char input;
    stack<char> s;
    bool flag = true;
    while((input = getchar()) != '\n'){//括号匹配
        if(input == '{' || input == '(' || input == '['){
            s.push(input);
        }else if(input == '}' && !s.empty()){
            if(s.top() == '{'){
                s.pop();
                continue;
            }else{
                flag = false;
                break;
            }
        }else if(input == ']' && !s.empty()){
            if(s.top() == '['){
                s.pop();
                continue;
            }else{
                flag = false;
                break;
            }
        }else if(input == ')' && !s.empty()){
            if(s.top() == '('){
                s.pop();
                continue;
            }else{
                flag = false;
                break;
            }
        }else{
            flag = false;
            break;
        }
    }
    if(!s.empty()){
        flag = false;
    }
    if(flag){
        cout << "Match" << endl;
    }else{
        cout << "Unmatch" << endl;
    }
    return 0;
}