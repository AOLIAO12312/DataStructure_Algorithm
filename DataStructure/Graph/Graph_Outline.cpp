#include<iostream>
using namespace std;

//图的存储方式：
//1.邻接矩阵法：空间复杂度O(n2),适合存储稠密图；无向图可以使用对称矩阵进行存储
//矩阵乘法可以计算从顶点i到顶点j长度为n（次方数）的路径数目

//2.邻接表法：
class VertexType {};//存储顶点的相关信息
class InfoType {};//存储边的相关信息
class ArcNode {//边
    public:
    int adjvex;//边指向哪一个顶点//邻接域
    ArcNode* next;//指向下一条边的指针
    InfoType info; //边权值
};
class VtxNode {
    public:
    VertexType data;//包含顶点相关信息
    ArcNode* first; //第一条边
};
class ALGraph {
    public:
    VtxNode* vertices;//通过数组存储顶点
    int vexnum, arcnum;//记录顶点个数和边的个数
};
//存储无向图，边节点有冗余，存储两倍边的数量；有向图无冗余
//邻接表适合存储稀疏图 表示方式不唯一
//找入边不方便

//3.十字链表法（有向图）
//只能用于存储有向图 更方便找到入边 表示方式不唯一

//4.邻接多重表法（无向图）
//方便找到入边 表示方式不唯一

int main() {

    return 0;
}