#include<iostream>
#define MAX_LEN 10
using namespace std;
template <class T>
class Queue{//队列
private:
    T data[MAX_LEN];
    int front;
    int rear;
public:
    Queue():front(0),rear(0){}
    inline bool isEmpty(){
        return front == rear;
    }
    inline bool isFull(){
        return (rear + 1) % MAX_LEN == front;
    }
    bool push_back(T t){//先进先出
        if(this->isFull()){
            cout << "Queue is full" << endl;
            return false;
        }else{
            data[rear] = t;
            rear = (rear + 1) % MAX_LEN;
            return true;
        }
    }
    bool pop_front(T& t){
        if(this->isEmpty()){
            cout << "Queue is empty" << endl;
            return false;
        }else{
            t = data[front];
            front = (front + 1) % MAX_LEN;
            return true;
        }
    }
    void show(){
        for(int i = 0;i<MAX_LEN;++i){
            cout << data[i] << " ";
        }
        cout << endl << front << "  " << rear << endl;
        cout << "size = " << this->getSize() << endl;
    }
    bool getHead(T& t){
        if(this->isEmpty()){
            cout << "Queue is empty" << endl;
            return false;
        }else{
            t = data[front];
            return true;
        }
    }
    int getSize(){
        return (rear + MAX_LEN - front) % MAX_LEN;
    }
};

int main(){
    Queue<int> q;
    q.push_back(10);
    q.push_back(20);
    q.push_back(30);
    q.push_back(540);
    q.show();
    int x;
    q.pop_front(x);
    q.show();
    cout << x << endl;
    q.push_back(x);
    cout << x << endl;
    q.show();
    return 0;
}