#include<iostream>
using namespace std;

template <class T>
class Node {
    public:
    T data;
    Node<T>* lchild, * rchild;
    Node() {
        lchild = nullptr;
        rchild = nullptr;
    }
};
template <class T>
class Tree {
    public:
    Node<T>* root;
    Tree() {
        root = new Node<T>();
    }

};

int main() {

    return 0;
}