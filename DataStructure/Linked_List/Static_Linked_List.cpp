#include<iostream>
#include<assert.h>
#define MAX_LEN 10
using namespace std;
template <class T>
class Node{
public:
    T data;
    int next;
public:
    Node(){
        data = T();
        next = -2;
    }
};
template <class T>
class SLinkedList{//静态链表
private:
    Node<T> list[MAX_LEN];
    int size;
public:
    SLinkedList(){
        list[0].next = -1;//指向NULL
        for(int i = 1;i<MAX_LEN;++i){
            list[i].next = -2;//表示空节点 未被使用
        }
        this->size = 0;
    }
    bool isEmpty(){
        if(list->next == -1){
            return true;
        }else{
            return false;
        }
    }
    Node<T>& getElem(int index){
        assert(this->size > 0);
        assert(index <= size && index >= 1);
        int currentNodeIndex = 0;
        int count = 0;
        while(count != index){
            currentNodeIndex = list[currentNodeIndex].next;
            ++count;
        }
        return list[currentNodeIndex];
    }
    int getAvailablePos(){
        for(int i = 1;i<MAX_LEN;++i){//索引为0为头节点，不遍历
            if(this->list[i].next == -2){
                return i;
            }
        }
        return -1;//如果没有空间就返回-1
    }
    bool push_back(T t){
        if(this->isEmpty() == true){
            //如果静态链表为空
            //将索引为1的地方设置为第一个区域
            list[0].next = 1;
            list[1].data = t;
            list[1].next = -1;
        }else{
            Node<T>& LastNode = this->getElem(this->size);
            int AvailablePos = this->getAvailablePos();
            if(AvailablePos != -1){
                this->list[AvailablePos].data = t;
                this->list[AvailablePos].next = -1;
                LastNode.next = AvailablePos;
            }else{
                cout << "Storage is full" << endl;
                return false;
            }
        }
        ++this->size;
        return true;
    }
    void printList(){
        int currentNodeIndex = 0;
        while(this->list[currentNodeIndex].next != -1){
            currentNodeIndex = this->list[currentNodeIndex].next;
            cout << this->list[currentNodeIndex].data << " ";
        }
        cout << endl;
    }
    void showList(){
        for(int i = 0;i<MAX_LEN;++i){
            cout << this->list[i].data << "\t" <<  this->list[i].next <<endl;
        }
    }
};

int main(){
    SLinkedList<int> sll;
    while(sll.push_back(10));
    sll.printList();
    sll.showList();
    return 0;
}