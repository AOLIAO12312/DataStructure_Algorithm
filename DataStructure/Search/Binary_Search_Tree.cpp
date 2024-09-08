#include<iostream>
#include<string>
#include<sstream>
#include<stack>
using namespace std;
template <class T>
class TNode {
    public:
    T data;
    TNode<T>* lchild, *rchild;
    TNode() {
        lchild = rchild = nullptr;
    }
    TNode(T t) {
        lchild = rchild = nullptr;
        this->data = t;
    }
};
template <class T>
class BST {//Binary Search Tree
    public:
    TNode<T> root;
    bool isEmpty;
    public:
    BST() {
        isEmpty = true;
    }
    TNode<T>* BST_Search(T target) {
        TNode<T>* tmpNode = &root;
        while (tmpNode != nullptr && target != tmpNode->data) {
            if (target < tmpNode->data) {
                tmpNode = tmpNode->lchild;
            } else {
                tmpNode = tmpNode->rchild;
            }
        }
        return tmpNode;
    }
    bool insertNode(T t) {
        if (isEmpty == true) {
            root.data = t;
            isEmpty = false;
        } else {
            TNode<T>* NewNode = new TNode<T>(t);
            TNode<T>* tmpNode = &root;
            while (tmpNode != nullptr) {
                if (t < tmpNode->data) {
                    if (tmpNode->lchild == nullptr) {
                        tmpNode->lchild = NewNode;
                        return true;
                    } else {
                        tmpNode = tmpNode->lchild;
                    }
                } else if (t > tmpNode->data) {
                    if (tmpNode->rchild == nullptr) {
                        tmpNode->rchild = NewNode;
                        return true;
                    } else {
                        tmpNode = tmpNode->rchild;
                    }
                } else if (t == tmpNode->data) {
                    cout << "Element exists, insert failed" << endl;
                    return false;
                }
            }
            return false;
        }
        return false;
    }
    bool deleteNode(T t) {
        TNode<T>* tmpNode = &root;
        TNode<T>* FatherNode;
        while (tmpNode != nullptr && tmpNode->data != t) {
            FatherNode = tmpNode;
            if (t < tmpNode->data) {
                tmpNode = tmpNode->lchild;
            } else if (t > tmpNode->data) {
                tmpNode = tmpNode->rchild;
            }
        }
        if (tmpNode == nullptr) {
            cout << "No such element, delete failed" << endl;
            return false;
        } else if (tmpNode->data == t) {
            if (tmpNode->lchild == nullptr && tmpNode->rchild == nullptr) {
                if (FatherNode->lchild == tmpNode) {
                    FatherNode->lchild = nullptr;
                } else {
                    FatherNode->rchild = nullptr;
                }
            } else if (tmpNode->rchild == nullptr && tmpNode->lchild != nullptr) {//左侧有孩子
                if (FatherNode->lchild == tmpNode) {
                    FatherNode->lchild = tmpNode->lchild;
                } else {
                    FatherNode->rchild = tmpNode->lchild;                    
                }
            } else if (tmpNode->rchild != nullptr && tmpNode->lchild == nullptr) {//右侧有孩子
                if (FatherNode->lchild == tmpNode) {
                    FatherNode->lchild = tmpNode->rchild;
                } else {
                    FatherNode->rchild = tmpNode->rchild;                    
                }         
            } else {//两侧均有孩子
                TNode<int>* tNode = tmpNode->rchild;
                while (tNode->lchild) {
                    tNode = tNode->lchild;//寻找最左侧节点
                }
                tmpNode->data = tNode->data;
                deleteNode(tNode->data);
                delete tNode;
            }
            return true;
        }
        cout << "???" << endl;
        return false;
    }
    void inOrder2(TNode<int>* Node) {//使用栈模拟递归实现
        stack<TNode<int>*> s;
        TNode<int>* t;
        s.push(Node);
        while (!s.empty()) {
            t = s.top();
            s.pop();
            while (t) {
                s.push(t);
                t = t->lchild;
            }
            if (s.empty())break;
            t = s.top();
            s.pop();
            visit(t);
            s.push(t->rchild);
        }
    }
    void inOrder(TNode<T>* tmpNode) {
        if (tmpNode != nullptr) {
            inOrder(tmpNode->lchild);
            visit(tmpNode);
            inOrder(tmpNode->rchild);
        }
    }
    void visit(TNode<T>* tmpNode) {
        cout << tmpNode->data << endl;
    }
};

int main() {
    BST<int> b;
    string input;
    getline(cin, input);
    stringstream ss(input);
    string token;
    while (ss >> token) {//34 55 67 12 2 43 71 89
        int i = stoi(token);
        b.insertNode(i);
    }
    b.inOrder2(&b.root);
    b.deleteNode(10);//7 3 5 8 6 9 2 4
    cout << endl;
    b.inOrder2(&b.root);
    return 0;
}