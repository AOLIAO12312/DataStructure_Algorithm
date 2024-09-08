#include<iostream>
#include<queue>
using namespace std;
enum { Pre, In, Pos };
template <class T>
class BiTNode {
    public:
    T data;
    BiTNode* lchild, * rchild;
    bool ltag, rtag;
    BiTNode() {
        lchild = NULL;
        rchild = NULL;
        ltag = false;
        rtag = false;
    }
    BiTNode(T t) {
        data = t;
        lchild = NULL;
        rchild = NULL;
        ltag = false;
        rtag = false;
    }
};
template <class T>
class BiTree {
    private:
    bool isEmpty;
    public:
    BiTNode<T> root;
    BiTNode<T>* pre;//用于辅助线索化二叉树的全局变量
    BiTree() :isEmpty(true) {}
    ~BiTree() {
        Delete(&root);
        cout << "Delete successfully" << endl;
    }
    void Delete(BiTNode<T>* Node) {
        if (Node != NULL) {
            if (Node->ltag == false && Node->lchild != NULL) {
                Delete(Node->lchild);
            }
            if (Node->rtag == false && Node->rchild != NULL) {
                Delete(Node->rchild);
            }
            if (Node != &root) {
                delete Node;
            }
        }
    }
    bool insertNode(T t) {
        if (isEmpty == true) {
            root.data = t;
            isEmpty = false;
            return true;
        } else {
            BiTNode<T>* NewNode = new BiTNode<T>(t);
            if (NewNode == NULL) {
                return false;
            }
            queue<BiTNode<T>*>qtn;
            qtn.push(&root);
            while (qtn.front()->lchild != NULL && qtn.front()->rchild != NULL) {
                qtn.push(qtn.front()->lchild);
                qtn.push(qtn.front()->rchild);
                qtn.pop();
            }
            if (qtn.front()->lchild == NULL) {
                qtn.front()->lchild = NewNode;
            } else {
                qtn.front()->rchild = NewNode;
            }
            return true;
        }
    }
    void LayersErgodic() {
        if (isEmpty != true) {
            queue<BiTNode<T>*>qtn;
            qtn.push(&root);
            while (!(qtn.front()->lchild == NULL || qtn.front()->ltag == true)
                && !(qtn.front()->rchild == NULL || qtn.front()->rtag == true)) {
                qtn.push(qtn.front()->lchild);//找到度不为2的节点中止
                qtn.push(qtn.front()->rchild);
                print(qtn.front());
                qtn.pop();
            }
            if (!(qtn.front()->lchild == NULL || qtn.front()->ltag == true)) {
                qtn.push(qtn.front()->lchild);
            }
            while (!qtn.empty()) {
                print(qtn.front());
                qtn.pop();
            }
        }
        cout << endl;
    }
    void Ergodic() {
        InOrder(&root);
        cout << endl;
    }
    void InOrder(BiTNode<T>* Node) {//递归方法中序遍历二叉树
        if (Node != NULL) {
            if (Node->ltag == false) {
                InOrder(Node->lchild);
            }
            print(Node);
            if (Node->rtag == false) {
                InOrder(Node->rchild);
            }
        }
    }
    BiTNode<T>* FirstNode_InOrder(BiTNode<T>* Node) {
        while (Node->ltag == false) {
            Node = Node->lchild;
        }
        return Node;//循环找到最左下节点，也是第一个被中序遍历的节点
    }
    BiTNode<T>* LastNode_InOrder(BiTNode<T>* Node) {
        while (Node->rtag == false) {
            Node = Node->rchild;
        }
        return Node;//循环找到最右下节点，也是最后一个被中序遍历的节点
    }
    BiTNode<T>* NextNode_InOrder(BiTNode<T>* Node) {
        if (Node->rtag == false) {
            return FirstNode_InOrder(Node->rchild);
        } else {
            return Node->rchild;//若rtag为true，则右子节点为线索化的下一节点
        }
    }
    BiTNode<T>* PreNode_InOrder(BiTNode<T>* Node) {//寻找节点的前驱节点
        if (Node->ltag == false) {
            return LastNode_InOrder(Node->lchild);
        } else {
            return Node->lchild;
        }
    }
    void InOrder_Thread() {//线索化中序遍历二叉树
        for (BiTNode<T>* Node = FirstNode_InOrder(&root);Node != NULL;Node = NextNode_InOrder(Node)) {
            print(Node);
        }
        cout << endl;
    }
    void InOrder_Reverse_Thread() {//线索化中序逆序遍历二叉树
        for (BiTNode<T>* Node = LastNode_InOrder(&root);Node != NULL;Node = PreNode_InOrder(Node)) {
            print(Node);
        }
        cout << endl;
    }
    void print(BiTNode<T>* Node) {
        cout << Node->data << " ";
    }
    void CreateThread(int Cmd) {
        pre = NULL;
        if (&root != NULL) {
            switch (Cmd) {
            case Pre:PreThread(&root);
                break;
            case In:InThread(&root);
                break;
            case Pos:PosThread(&root);
                break;
            default:
                cout << "Command is invalid" << endl;
                break;
            }
            if (pre->rchild == NULL) {
                pre->rtag = true;
            }
        }
        cout << "Create thread successfully" << endl;
    }
    void InThread(BiTNode<T>* Node) {//中序线索化二叉树
        if (Node != NULL) {
            if (Node->ltag == false) {
                InThread(Node->lchild);//中序遍历左子树
            }
            visit2(Node);//访问根节点
            if (Node->rtag == false) {
                InThread(Node->rchild);//中序遍历右子树
            }
        }
    }
    void PreThread(BiTNode<T>* Node) {//前序线索化二叉树
        if (Node != NULL) {
            visit2(Node);//访问根节点
            if (Node->ltag == false) {
                PreThread(Node->lchild);//前序遍历左子树
            }
            if (Node->rtag == false) {
                PreThread(Node->rchild);//前序遍历右子树
            }
        }
    }
    void PosThread(BiTNode<T>* Node) {//后序线索化二叉树
        if (Node != NULL) {
            if (Node->ltag == false) {
                PosThread(Node->lchild);//后序遍历左子树
            }
            if (Node->rtag == false) {
                PosThread(Node->rchild);//后序遍历右子树
            }
            visit2(Node);//访问根节点
        }
    }
    void visit2(BiTNode<T>* Node) {
        if (Node->lchild == NULL) {//左子树为空则建立前驱线索
            Node->lchild = pre;
            Node->ltag = true;
        }
        if (pre != NULL && pre->rchild == NULL) {
            pre->rchild = Node;//建立前驱节点的后继线索
            pre->rtag = true;
        }
        pre = Node;
    }

};

int main() {
    BiTree<int>bit;
    for (int i = 0;i < 12;++i) {
        bit.insertNode(i);
    }
    bit.Ergodic();//递归遍历二叉树
    bit.CreateThread(In);
    bit.InOrder_Thread();//线索化中序遍历二叉树
    bit.InOrder_Reverse_Thread();//线索化中序逆序遍历二叉树
    bit.LayersErgodic();
    return 0;
}