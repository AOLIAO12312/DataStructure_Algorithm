#include<iostream>
#include<assert.h>
#include<string>
#include<sstream>
using namespace std;
enum { BLACK, RED };//BLACK = 0,RED = 1
template <class T>
class Node {
    public:
    T data;
    Node<T>* lchild, * rchild;
    Node<T>* parent;
    int color;
    Node() {
        parent = lchild = rchild = nullptr;
        color = RED;
    }
    Node(T t) {
        parent = lchild = rchild = nullptr;
        color = RED;
        data = t;
    }
};
template <class T>
class RBT {//Red_Black_Tree
    public:
    Node<T>* root;
    RBT() {
        root = nullptr;
    }
    int getColor(Node<T>* Node) {
        return (Node == nullptr) ? BLACK : Node->color;
    }
    bool insertNode(T t) {
        if (root == nullptr) {//插入根节点
            root = new Node<T>(t);//根节点颜色为黑
            return adjustTree(root);
        } else {//插入非根节点
            Node<T>* NewNode = new Node<T>(t);//默认设置为RED
            Node<T>* tmpNode = root;//tmpNode用于遍历
            while (true) {
                if (t < tmpNode->data) {
                    if (tmpNode->lchild == nullptr) {
                        //插入节点
                        tmpNode->lchild = NewNode;
                        NewNode->parent = tmpNode;
                        break;
                    } else {//转向左子树
                        tmpNode = tmpNode->lchild;
                    }
                } else {
                    if (tmpNode->rchild == nullptr) {
                        tmpNode->rchild = NewNode;
                        NewNode->parent = tmpNode;
                        break;
                    } else {
                        tmpNode = tmpNode->rchild;
                    }
                }
            }
            return adjustTree(NewNode);
        }

    }
    bool adjustTree(Node<T>* NewNode) {//根据新节点进行红黑树的调整
        assert(NewNode != nullptr);
        if (NewNode == root) {
            NewNode->color = BLACK;//根节点颜色为黑
        } else if (getColor(NewNode->parent) == RED) {//若发现连续的两红色节点（新插入的节点一定是红色）
            if (getColor(uncleNode(NewNode)) == RED) {//红叔
                renew_F_GF_Un_color(NewNode);
                adjustTree(NewNode->parent->parent);//将爷节点作为新节点进行调整
            } else {//黑叔 进行旋转+染色
                Node<T>* f = NewNode->parent;
                Node<T>* gf = f->parent;
                if (gf->lchild == f) {//L
                    if (f->lchild == NewNode) {
                        //LL
                        RightRotate(f);
                        f->color = (f->color == RED) ? BLACK : RED;
                        gf->color = (gf->color == RED) ? BLACK : RED;
                    } else if (f->rchild == NewNode) {
                        //LR
                        LeftRotate(NewNode);
                        RightRotate(NewNode);
                        NewNode->color = (NewNode->color == RED) ? BLACK : RED;
                        gf->color = (gf->color == RED) ? BLACK : RED;
                    }
                } else if (gf->rchild == f) {//R
                    if (f->lchild == NewNode) {
                        RightRotate(NewNode);
                        LeftRotate(NewNode);
                        NewNode->color = (NewNode->color == RED) ? BLACK : RED;
                        gf->color = (gf->color == RED) ? BLACK : RED;
                        //RL
                    } else if (f->rchild == NewNode) {
                        //RR
                        LeftRotate(f);
                        f->color = (f->color == RED) ? BLACK : RED;
                        gf->color = (gf->color == RED) ? BLACK : RED;
                    }
                }
            }
        }
        return true;
    }
    bool renew_F_GF_Un_color(Node<T>* p) {//叔父爷反转染色
        assert(p->parent != root);
        Node<T>* f = p->parent;
        Node<T>* gf = p->parent->parent;
        Node<T>* un = uncleNode(p);
        f->color = (f->color == RED) ? BLACK : RED;
        gf->color = (gf->color == RED) ? BLACK : RED;
        un->color = (un->color == RED) ? BLACK : RED;//不可能是黑色
        return true;
    }
    Node<T>* uncleNode(Node<T>* p) {
        assert(p->parent != root);
        Node<T>* f = p->parent;
        Node<T>* gf = p->parent->parent;
        return (gf->lchild == f) ? gf->rchild : gf->lchild;
    }
    void RightRotate(Node<T>* p) {//将Node与其父节点进行右旋操作
        assert(p->parent != nullptr);
        Node<T>* f = p->parent;
        Node<T>* gf = f->parent;
        f->lchild = p->rchild;
        p->rchild = f;
        p->rchild->parent = f;
        f->parent = p;
        if (gf != nullptr) {//若g不是root节点
            if (gf->lchild == f) {
                gf->lchild = p;
            } else {
                gf->rchild = p;
            }
            p->parent = gf;
        } else {
            root = p;
            p->parent = root;
            root->parent = nullptr;
        }
    }
    void LeftRotate(Node<T>* p) {//将Node与其父节点进行左旋操作
        assert(p->parent != nullptr);
        Node<T>* f = p->parent;
        Node<T>* gf = f->parent;
        f->rchild = p->lchild;
        p->lchild = f;
        p->lchild->parent = f;
        f->parent = p;
        if (gf != nullptr) {//若g不是root节点
            if (gf->lchild == f) {
                gf->lchild = p;
            } else {
                gf->rchild = p;
            }
            p->parent = gf;
        } else {
            root = p;
            p->parent = root;
            root->parent = nullptr;
        }
    }
    void inOrder(Node<T>* Node) {
        if (Node != nullptr) {
            inOrder(Node->lchild);
            cout << Node->data << " ";
            inOrder(Node->rchild);
        }
    }
};


int main() {
    RBT<int> t;
    string input;
    getline(cin, input);
    stringstream ss(input);
    string token;
    while (ss >> token) {
        t.insertNode(stoi(token));
    }
    t.inOrder(t.root);
    return 0;
}