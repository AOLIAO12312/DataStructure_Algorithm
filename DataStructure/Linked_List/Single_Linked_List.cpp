#include<iostream>
#include<string>
#include<assert.h>
using namespace std;
template <class T>
class LNode{//单链表
public:
    T data;//数据域
    LNode* next;//指针域
    LNode(){
        this->data = T();
        this->next = NULL;
    }
    LNode(T Data){
        this->data = Data;
        this->next = NULL;
    }
};
template <class T>
class LinkedList{
private:
    LNode<T> head;
    LNode<T>* LastNode;//记录最后一个节点的位置 //方便尾插
    int size;
public:
    LinkedList(){
        //带头节点的单链表初始化
        //后续操作会更方便
        LastNode = NULL;
        size = 0;//链表长度初始化为0
    }
    ~LinkedList(){
        //释放内存空间
        LNode<T>* formerNode = &(this->head);
        LNode<T>* nextNode = head.next;
        while (formerNode->next != NULL){
            if(formerNode != &(this->head)){
                delete formerNode;
            }
            formerNode = nextNode;
            nextNode = nextNode->next;
        }
        //cout << "Delete successfully" << endl;
    }
    bool isEmpty(){
        if(head.next == NULL){//判断链表是否为空
            return true;
        }else{
            return false;
        }
    }
    bool push_back(T t){//在尾部插入节点//尾插法 O(1) 需要记录尾部节点的位置
        LNode<T>* Node = new LNode<T>(t);
        if(Node == NULL){
            cout << "Memory allocated failed" << endl;
            return false;
        }
        if(this->isEmpty() == true){//表为空
            head.next = Node;
        }else{
            LastNode->next = Node;
        }
        LastNode = Node;//更新类中最后一个节点
        ++this->size;
        return true;
    }
    bool push_front(T t){//头插
        return this->listInsert(1,t);
    }
    int getSize(){
        return this->size;
    }
    LNode<T>* getElem(int index){//索引从1开始
        assert(index <= this->size);
        assert(index >= 0);
        int count = 0;
        LNode<T>* Node = &(this->head);//此节点用于遍历
        while(Node != NULL && count <= this->size){
            if(count == index){
                return Node;
            }else{
                Node = Node->next;
                ++count;
            }
        }
        assert(false);
        return NULL;
    }
    bool listInsert(int insertPos,T t){//在第i个位置 插入元素(将该元素作为第i个元素)
        assert(insertPos <= this->size + 1);//允许查在表尾
        assert(insertPos >= 1);
        if(insertPos == this->size + 1){
            return push_back(t);//如果插入的是最后一个元素直接调用push_back函数提高运行效率
        }
        return InsertNextNode(getElem(insertPos - 1),t);//封装为函数
    }
    bool InsertNextNode(LNode<T>* Node,T t){//Node为指定结点，需要在它后面插入元素
        assert(Node != NULL);
        LNode<T>* NewNode = new LNode<T>(t);
        if(NewNode == NULL){
            cout << "Memory allocted failed" << endl;
            return false;
        }else{
            NewNode->next = Node->next;
            Node->next = NewNode;
            ++this->size;
            return true;
        }
    }
    bool InsertPreNode(LNode<T>* Node,T t){//Node为指定结点，需要在它前面插入元素
        assert(Node != NULL);
        LNode<T>* NewNode = new LNode<T>(Node->data);
        if(NewNode == NULL){
            cout << "Memory allocted failed" << endl;
            return false;
        }else{
            Node->data = t;//等于后插再交换数据位置
            NewNode->next = Node->next;
            Node->next = NewNode;
            return true;
        }
    }

    //若给出节点，则前插和后插的时间复杂度都为O(1)
    //需要考虑给出节点为最后一个节点的情况
    bool Delete(int index){//从1开始索引，头节点为第0个节点
        assert(index <= this->size && index >= 1);
        LNode<T>* Node = getElem(index - 1);
        LNode<T>* DeleteNode = Node->next;
        Node->next = DeleteNode->next;
        delete DeleteNode;
        --this->size;
        return true;
    }

    void show(){//需要重载<<
        LNode<T>* Node = &(this->head);//此节点用于遍历
        while (Node->next != NULL){
            Node = Node->next;
            cout << Node->data  << " ";
        }
        cout << endl;
        cout << "Size = " << this->size << endl;
    }
};

class Stu{
public:
    string Name;
    int Age;
    Stu(){
        Name = "NULL";
        Age = -1;
    }
    Stu(string name,int age):Name(name),Age(age){}
    Stu(const Stu& s){
         this->Age = s.Age;
         this->Name = s.Name;
    }
};//任意数据类型测试
ostream& operator<<(ostream& cout,Stu s){//重载<<运算符
    cout << s.Name << " " << s.Age;
    return cout;
}

int main(){
    LinkedList<int> ll;
    for(int i = 0;i<10;++i){
        ll.push_back(i);
        ll.push_front(i);//单链表的逆置
    }
    ll.push_front(256);
    ll.show();
    return 0;
}