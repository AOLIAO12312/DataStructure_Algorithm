#include<iostream>
#define MAX_SIZE 10
using namespace std;
//邻接矩阵法
class Vertex {
    public:
};
class AMGraph {//Adjacency Matrix Graph
    private:
    int Matrix[MAX_SIZE][MAX_SIZE];
    Vertex vertices[MAX_SIZE];
    int size;
    public:
    AMGraph() {
        for (int i = 0;i < MAX_SIZE;++i) {
            for (int j = 0;j < MAX_SIZE;++j) {
                Matrix[i][j] = 0;
            }
        }
    }
    ~AMGraph() {}
    bool Adjacent(int x, int y) {}//判断图G是否存在边（x，y）(x,y)表示节点
    void Neighbors(int x) {}//列出图G与x邻接的边
    bool InsertVertex(Vertex v) {}//在图G插入顶点x
    bool DeleteVertex(int x) {}//删除顶点
    bool AddEdge(int x, int y) {}//添加链接x，y的边
    int FirstNeighbor(int x) {}//找到与x相连的第一个节点，没有则返回-1
    
};
int main() {
    AMGraph g;
    return 0;
}