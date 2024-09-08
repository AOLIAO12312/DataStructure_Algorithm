#include<iostream>
#include<vector>
#include<limits>
#include<string>
#include<assert.h>
#include<queue>
#define MAX_SIZE 10
using namespace std;
//邻接矩阵法
class Vertex {
    public:
    string Name;
    bool isOccupied;
    Vertex(string name) {
        Name = name;
        isOccupied = true;
    }
    Vertex() {
        Name = "null";
        isOccupied = false;
    }
};
class AMGraph {//Adjacency Matrix Graph
    private:
    int Matrix[MAX_SIZE][MAX_SIZE];
    Vertex vertices[MAX_SIZE];
    bool visited[MAX_SIZE];
    int size;
    public:
    AMGraph() {
        for (int i = 0;i < MAX_SIZE;++i) {
            for (int j = 0;j < MAX_SIZE;++j) {
                Matrix[i][j] = INT_MAX;
            }
        }
        size = 0;
    }
    ~AMGraph() {}
    bool Adjacent(int x, int y) {
        return Matrix[x][y];
    }//判断图G是否存在边（x，y）(x,y)表示节点
    void Neighbors(int x) {
        assert(vertices[x].isOccupied == true);
        for (int i = 0;i < size;++i) {
            if (vertices[i].isOccupied == true) {
                if (Matrix[x][i]) {
                    cout << vertices[i].Name << " ";
                }
            }
        }
        cout << endl;
    }//列出图G与x邻接的顶点
    bool InsertVertex(int x, string Name) {
        assert(x < MAX_SIZE && x >= 0);
        if (vertices[x].isOccupied == false) {
            vertices[x].isOccupied = true;
            vertices[x].Name = Name;
            ++size;
            return true;
        } else {
            cout << x << " position has been occupied" << endl;
            return false;
        }

    }//在图G插入顶点x
    bool DeleteVertex(int x) {
        assert(x < MAX_SIZE && x >= 0);
        if (vertices[x].isOccupied == true) {
            vertices[x].isOccupied == false;
            for (int i = 0;i < MAX_SIZE;++i) {
                Matrix[i][x] = 0;
                Matrix[x][i] = 0;//清空路径数据
            }
            --size;
            return true;
        } else {
            return false;
        }
    }//删除顶点
    bool AddEdge(int x, int y,int weight) {
        Matrix[x][y] = weight;
        Matrix[y][x] = weight;
        return true;
    }//添加链接x，y的边
    int FirstNeighbor(int x) {
        assert(vertices[x].isOccupied == true);
        for (int i = 0;i < size;++i) {
            if (vertices[i].isOccupied == true) {
                if (Matrix[x][i]) {
                    return i;
                }
            }
        }
        return -1;
    }//找到与x相连的第一个节点，没有则返回-1
    int NextNeighbor(int x, int y) {//寻找x顶点y之后的邻接点，没有则返回-1
        assert(vertices[x].isOccupied == true);
        for (int i = y + 1;i < size;++i) {
            if (vertices[i].isOccupied == true) {
                if (Matrix[x][i]) {
                    return i;
                }
            }
        }
        return -1;
    }
    void Show() {
        cout << "  ";
        for (int i = 0;i < MAX_SIZE;++i) {
            cout << vertices[i].Name << " ";
        }
        cout << endl;
        for (int i = 0;i < MAX_SIZE;++i) {
            cout << vertices[i].Name << " ";
            for (int j = 0;j < MAX_SIZE;++j) {
                cout << (Matrix[i][j] == INT_MAX ? 0 : Matrix[i][j]) << " ";
            }
            cout << endl;
        }
    }
    void visit(int v) {
        cout << vertices[v].Name << " " << v << endl;
    }
    void BFSTraverse() {//遍历插入的所有节点（包括非连通图），广度优先遍历
        for (int i = 0;i < MAX_SIZE;++i) {
            visited[i] = false;
        }
        for (int i = 0;i < size;++i) {
            if (!visited[i]) {
                BFS(i);
            }
        }
    }
    void BFS(int v) {//从顶点v出发，广度优先遍历图G    
        queue<int> qv;
        visit(v);
        visited[v] = true;
        qv.push(v);
        while (!qv.empty()) {
            v = qv.front();
            qv.pop();
            for (int w = FirstNeighbor(v);w >= 0;w = NextNeighbor(v, w)) {
                //检测v的所有邻接点
                if (!visited[w]) {
                    visit(w);
                    visited[w] = true;
                    qv.push(w);
                }
            }
        }
    }
    void DFSTraverse() {//深度优先遍历
        for (int i = 0;i < MAX_SIZE;++i) {
            visited[i] = false;
        }
        for (int i = 0;i < size;++i) {
            if (!visited[i]) {
                DFS(i);
            }
        }
    }
    void DFS(int v) {
        visit(v);
        visited[v] = true;
        for (int w = FirstNeighbor(v);w >= 0;w = NextNeighbor(v, w)) {
            if (!visited[w]) {
                DFS(w);
            }
        }
    }
    int primMST() {//最小生成树prim算法
        vector<bool> isJoin(size, false);
        vector<int> lowCost(size, INT_MAX);
        lowCost[0] = 0;

        int parent[size];
        for (int i = 0;i < size;++i) {
            parent[i] = -1;//初始化生成树
        }
        int mstweight = 0;//存放生成树的权重
        for (int count = 0;count < size - 1;++count) {
            int u = -1;
            for (int v = 0;v < size;++v) {
                if (!isJoin[v] && ((u == -1) || (lowCost[v] < lowCost[u]))) {
                    u = v;//找到最近的顶点（路程花销最小顶点为u）
                }
            }
            isJoin[u] = true;//将路程最近的顶点加入树
            for (int v = 0;v < size;++v) {
                if (Matrix[u][v] && !isJoin[v] && Matrix[u][v] < lowCost[v]) {
                    parent[v] = u;//设置顶点的父节点（可能被覆盖）
                    lowCost[v] = Matrix[u][v];//如果某顶点的位置比之前更近 更新lowCost数组
                }
            }
            mstweight += lowCost[u];
        }

        for (int i = 0;i < size;++i) {
            cout << parent[i] << " ";
        }
        cout << endl;
        return mstweight;
    }
};
int main() {
    AMGraph g;
    for (int i = 0;i < 7;++i) {
        g.InsertVertex(i, string(1, 'A' + i));//插入顶点
    }
    g.AddEdge(0, 1, 6);
    g.AddEdge(1, 3, 5);
    g.AddEdge(1, 4, 3);
    g.AddEdge(3, 4, 6);
    g.AddEdge(4, 5, 6);
    g.AddEdge(3, 5, 4);
    g.AddEdge(2, 5, 2);
    g.AddEdge(0, 2, 5);
    g.AddEdge(0, 3, 1);
    g.AddEdge(2, 3, 4);
    g.Show();//显示矩阵
    cout << g.primMST() << endl;//最小生成树
    return 0;
}