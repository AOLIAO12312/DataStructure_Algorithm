#include<iostream>
#define MAX_LEN 100
using namespace std;
template <class T>
class Stack{
private:
    T data[MAX_LEN];
    int top;
public:
    Stack():top(-1){}
    void clear(){
        top = -1;
    }
    bool isEmpty(){
        return top == -1;
    }
    bool push(T t){
        if(this->top == MAX_LEN - 1){
            cout << "Push failed, Stack is full" << endl;
            return false;
        }
        this->data[++this->top] = t;
        return true;
    }
    bool pop(T& t){
        if(this->top == -1){
            return false;
        }else{
            t = this->data[this->top--];
            return true;
        }
    }
    bool getTop(T& t){
        if(this->top == -1){
            return false;
        }else{
            t = this->data[this->top];
            return true;
        }
    }
};

int main(){
    Stack<int> s;
    cout << s.isEmpty() << endl;
    for(int i = 0;i<100;++i){
        s.push(i);
    }
    int x;
    while (s.pop(x)){
        cout << x << endl;
    }
    return 0;
}
