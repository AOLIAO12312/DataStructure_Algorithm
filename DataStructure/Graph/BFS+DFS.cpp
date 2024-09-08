#include<iostream>
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
                Matrix[i][j] = 0;
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
    bool AddEdge(int x, int y) {
        Matrix[x][y] = 1;
        Matrix[y][x] = 1;
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
                cout << Matrix[i][j] << " ";
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
};
int main() {
    AMGraph g;
    for (int i = 0;i < MAX_SIZE;++i) {
        g.InsertVertex(i, string(1, 'A' + i));
    }
    g.AddEdge(0, 1);
    g.AddEdge(0, 4);
    g.AddEdge(1, 5);
    g.AddEdge(5, 6);
    g.AddEdge(5, 2);
    g.AddEdge(2, 3);
    g.AddEdge(6, 3);
    g.AddEdge(6, 7);
    g.AddEdge(3, 7);
    g.AddEdge(2, 6);
    g.Show();
    g.BFSTraverse();
    cout << endl;
    g.DFSTraverse();
    return 0;
}