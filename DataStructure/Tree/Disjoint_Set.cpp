#include<iostream>
#include<assert.h>
#define MAX_TREE_SIZE 100
using namespace std;
template <class T>
class TNode {
    public:
    T data;
    int parent;//双亲位置域
    TNode() {
        parent = -1;
    }
};
template <class T>
class Tree {
    private:
    TNode<T> UFset[MAX_TREE_SIZE];
    int size;
    public:
    Tree() {
        for (int i = 0;i < MAX_TREE_SIZE;++i) {
            UFset[i].parent = -1;
            size = 0;
        }
    }
    bool insert(T t) {
        UFset[size].data = t;
        ++this->size;
        return true;
    }
    int Find(int x) {
        while (UFset[x].parent >= 0) {
            x = UFset[x].parent;
        }
        return x;
    }
    void Union(int root1, int root2) {
        assert(root1 < size && root2 < size);
        if (root1 == root2)return;
        if (UFset[root2].parent >= UFset[root1].parent) {
            UFset[root1].parent += UFset[root2].parent;
            UFset[root2].parent = root1;
        } else {
            UFset[root2].parent += UFset[root1].parent;
            UFset[root1].parent = root2;
        }
    }
    void Show() {
        for (int i = 0;i < size;++i) {
            cout << UFset[i].parent << " ";
        }
    }
};
int main() {
    Tree<char>t;
    for (int i = 0;i < 13;++i) {
        t.insert('A' + i);
    }
    t.Union(4, 11);
    t.Union(4, 10);
    t.Union(1, 4);
    t.Union(1, 5);
    t.Union(0, 1);
    t.Union(2, 6);
    t.Union(7, 12);
    t.Union(3, 7);
    t.Union(3, 8);
    t.Union(3, 9);

    t.Show();
    cout << endl;
    for (int i = 0;i < 13;++i) {
        cout << t.Find(i) << " ";
    }
    return 0;
}