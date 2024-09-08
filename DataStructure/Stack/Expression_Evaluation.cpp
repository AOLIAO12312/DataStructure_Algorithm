#include<iostream>
#include<string>
#include<stack>
#include<sstream>
#include<unordered_map>
#include<functional>
using namespace std;

//Polish notation 波兰表达式 = 前缀表达式
//Reverse Polish notation 逆波兰表达式 = 后缀表达式
unordered_map<char, function<int(int, int)>> ops = {  
    {'+', [](int a, int b) { return a + b; }},  
    {'-', [](int a, int b) { return a - b; }},  
    {'*', [](int a, int b) { return a * b; }},  
    {'/', [](int a, int b) {  
        if (b != 0) return a / b;  
        throw std::runtime_error("Division by zero");  
    }}  
};  

int priority(char c){
    switch(c){
        case '+':case '-':return 0;break;
        case '*':case '/':return 1;break;
        default:return -1;
    }
}

void showStack(stack<char>s){
    while(!s.empty()){
        cout << s.top() << endl;
        s.pop();
    }
}
bool isNum(const string& token){
    for(int i = 0;i<token.size();++i){
        if(token.at(i)<'0' || token.at(i) > '9'){
            return false;
        }
    }
    return true;
}

string InfixtoRpn(string expression){
    stack<char>operatorStack;
    stringstream InfixEx(expression);
    stringstream Rpn;
    string token;
    while(InfixEx >> token){
        if(isNum(token)){
            Rpn << token << " ";
        }else{
            char op = token.at(0);
            if(op == '(' || operatorStack.empty()){
                operatorStack.push(op);
            }else if(op == ')'){
                while(operatorStack.top() != '('){
                    Rpn << operatorStack.top() << " ";
                    operatorStack.pop();
                }
                operatorStack.pop();//弹出（ 括号处理完毕
            }else{
                while(!operatorStack.empty() && priority(op) <= priority(operatorStack.top())){
                    Rpn << operatorStack.top() << " ";
                    operatorStack.pop();
                }
                operatorStack.push(op);
            }
        }
    }
    while(!operatorStack.empty()){
        Rpn << operatorStack.top() << " ";
        operatorStack.pop();
    }
    return Rpn.str();
}
int EvaluateRpn(string exp){
    stringstream Rpn(exp);
    stack<int> numbers;
    string token;
    while(Rpn >> token){
        if(isNum(token)){
            numbers.push(stoi(token));
        }else{
            int num2 = numbers.top();
            numbers.pop();
            int num1 = numbers.top();
            numbers.pop();
            numbers.push(ops[token.at(0)](num1,num2));
        }
    }
    return numbers.top();
}
int main(){
    string exp;
    getline(cin, exp);
    cout << InfixtoRpn(exp) << endl;//中缀表达式转化为后缀表达式
    cout << EvaluateRpn(InfixtoRpn(exp)) << endl;//计算后缀表达式的值
    return 0;
}