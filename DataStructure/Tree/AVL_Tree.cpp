#include<iostream>
#include<string>
#include<sstream>
#include<assert.h>
#include<stack>
#include<math.h>
using namespace std;
template <class T>
class TNode {
    public:
    T data;
    TNode<T>* lchild, * rchild;
    TNode<T>* parent;//寻找父节点
    int height;
    TNode() {
        parent = lchild = rchild = nullptr;
        this->height = 0;
    }
    TNode(T t) {
        parent = lchild = rchild = nullptr;
        this->data = t;
        this->height = 0;
    }
};
template <class T>
class BST {//Binary Search Tree
    public:
    TNode<T>* root;
    bool isEmpty;
    public:
    BST() {
        root = new TNode<T>();
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
    unsigned int UpdateHeightUniverse(TNode<T>* Node) {//从root开始通过递归重新计算height,消耗较多的资源
        if (Node->lchild == nullptr && Node->rchild == nullptr) {
            Node->height = 1;
        } else if (Node->lchild != nullptr && Node->rchild == nullptr) {
            Node->height = UpdateHeightUniverse(Node->lchild) + 1;
        } else if (Node->lchild == nullptr && Node->rchild != nullptr) {
            Node->height = UpdateHeightUniverse(Node->rchild) + 1;
        } else {
            Node->height = max(UpdateHeightUniverse(Node->lchild) + 1, UpdateHeightUniverse(Node->rchild) + 1);
        }
        return Node->height;
    }
    void UpdateHeight(TNode<T>* Node) {//从某个节点向上更新高度，确保是新加入的节点
        //新加入的节点高度必为1
        while (Node != nullptr) {
            if (Node->lchild == nullptr && Node->rchild == nullptr) {//新加入节点的情况
                Node->height = 1;
            }else if (Node->lchild != nullptr && Node->rchild == nullptr) {
                Node->height = Node->lchild->height + 1;
            } else if (Node->lchild == nullptr && Node->rchild != nullptr) {
                Node->height = Node->rchild->height + 1;
            } else {
                Node->height = max(Node->lchild->height + 1,Node->rchild->height + 1);
            }
            Node = Node->parent;       
        }
        
    }
    bool insertNode(T t) {
        if (isEmpty == true) {
            root->data = t;
            isEmpty = false;
            UpdateHeight(root);
            return true;
        } else {
            TNode<T>* NewNode = new TNode<T>(t);
            TNode<T>* tmpNode = root;
            while (tmpNode != nullptr) {
                if (t < tmpNode->data) {
                    if (tmpNode->lchild == nullptr) {
                        tmpNode->lchild = NewNode;//插入左节点
                        NewNode->parent = tmpNode;
                        break;
                    } else {
                        tmpNode = tmpNode->lchild;//转向左子树
                    }
                } else if (t > tmpNode->data) {
                    if (tmpNode->rchild == nullptr) {
                        tmpNode->rchild = NewNode;//插入右节点
                        NewNode->parent = tmpNode;
                        break;
                    } else {
                        tmpNode = tmpNode->rchild;//转向右子树
                    }
                } else if (t == tmpNode->data) {
                    cout << "Element exists, insert failed" << endl;//已存在相同元素，插入失败
                    return false;
                }
            }
            UpdateHeight(NewNode);//更新节点高度信息
            //更新后的二叉树不一定是平衡二叉树
            //需要进行平衡

            return balanceTree(NewNode);
        }
    }
    bool balanceTree(TNode<T>* Node) {//从Node节点向上寻找不平衡节点，并进行平衡
         //为了构建平衡二叉树
         //从插入的节点开始向上查找平衡因子绝对值大于一的节点
        TNode<T>* tmpNode = Node;
        while (tmpNode != nullptr && tmpNode->parent != nullptr) {
            tmpNode = tmpNode->parent;
            if (abs(getHeight(tmpNode->lchild) - getHeight(tmpNode->rchild)) > 1) {//找到不平衡的节点
                if (getHeight(tmpNode->lchild) > getHeight(tmpNode->rchild)) {//L
                    if (getHeight(tmpNode->lchild->lchild) > getHeight(tmpNode->lchild->rchild)) {//L
                        //处理LL情况
                        RightRotate(tmpNode->lchild);
                    } else {
                        //处理LR情况
                        LeftRotate(tmpNode->lchild->rchild);
                        RightRotate(tmpNode->lchild);
                    }
                } else {
                    if (getHeight(tmpNode->rchild->lchild) > getHeight(tmpNode->rchild->rchild)) {//R
                        //处理RL情况
                        RightRotate(tmpNode->rchild->lchild);
                        LeftRotate(tmpNode->rchild);
                    } else {
                        //处理RR情况
                        LeftRotate(tmpNode->rchild);
                    }
                }
            }
            UpdateHeight(tmpNode);
         }
         return true;
    }
    int getHeight(TNode<T>* Node) {
        if (Node == nullptr) {
            return 0;
        } else {
            return Node->height;
        }
    }
    void RightRotate(TNode<T>* p) {//将Node与其父节点进行右旋操作
        assert(p->parent != nullptr);
        TNode<T>* f = p->parent;
        TNode<T>* gf = f->parent;
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
    void LeftRotate(TNode<T>* p) {//将Node与其父节点进行左旋操作
        assert(p->parent != nullptr);
        TNode<T>* f = p->parent;
        TNode<T>* gf = f->parent;
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
    bool deleteNode(T t) {
        TNode<T>* tmpNode = root;
        while (tmpNode != nullptr && tmpNode->data != t) {
            if (t < tmpNode->data) {
                tmpNode = tmpNode->lchild;
            } else if (t > tmpNode->data) {
                tmpNode = tmpNode->rchild;
            }
        }
        return deleteNode(tmpNode);
    }
    bool deleteNode(TNode<T>* tmpNode) {
        if (tmpNode == nullptr) {
            cout << "No such element, delete failed" << endl;
            return false;
        } else {
            TNode<T>* FatherNode = tmpNode->parent;
            if (tmpNode->lchild == nullptr && tmpNode->rchild == nullptr) {
                if (FatherNode->lchild == tmpNode) {
                    FatherNode->lchild = nullptr;
                } else {
                    FatherNode->rchild = nullptr;
                }
                delete tmpNode;
                tmpNode = nullptr;
            } else if (tmpNode->rchild == nullptr && tmpNode->lchild != nullptr) {//左侧有孩子
                if (FatherNode->lchild == tmpNode) {
                    FatherNode->lchild = tmpNode->lchild;
                } else {
                    FatherNode->rchild = tmpNode->lchild;                    
                }
                delete tmpNode;
                tmpNode = nullptr;
            } else if (tmpNode->rchild != nullptr && tmpNode->lchild == nullptr) {//右侧有孩子
                if (FatherNode->lchild == tmpNode) {
                    FatherNode->lchild = tmpNode->rchild;
                } else {
                    FatherNode->rchild = tmpNode->rchild;                    
                }
                delete tmpNode;
                tmpNode = nullptr;
            } else {//两侧均有孩子
                TNode<int>* tNode = tmpNode->rchild;
                while (tNode->lchild) {
                    tNode = tNode->lchild;//寻找右子树中序遍历后继节点
                }
                tmpNode->data = tNode->data;//将其与前驱节点/后继节点进行数据替换，然后递归删除其前驱节点/后继节点
                deleteNode(tNode);
            }
            if (FatherNode != nullptr) {
                UpdateHeight(FatherNode);//删除后更新节点高度信息
            }
            balanceTree(FatherNode);
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
        cout << tmpNode->data << "  Height = " << tmpNode->height << endl;
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
    // for (int i = 5;i > 0;--i) {
    //     b.insertNode(i);
    // }
    //system("pause");
    b.inOrder2(b.root);
    b.deleteNode(4);
    cout << endl;
    b.inOrder2(b.root);
    return 0;
}