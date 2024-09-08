#include<iostream>
#include<vector>
#include<limits>
#include<string>
#include<assert.h>
#include<queue>
#define MAX_SIZE 20
using namespace std;
void print(vector<int> v) {
    for (int i = 0;i < v.size();++i) {
        cout << v[i] << " ";
    }
    cout << endl;
}

class Edge {
public:
    int weight;
    string name;
    Edge() {
        weight = INT_MAX;
        name = "null";
    }
    Edge(int Weight, string Name) {
        this->weight = Weight;
        name = Name;
    }
};

class AOEGraph {
private:
    Edge Matrix[MAX_SIZE][MAX_SIZE];
    int size;
public:
    AOEGraph() {
        this->size = 0;
    }
    void InsertVertex() {//不保存节点称号
        ++this->size;
    }
    void AddEdge(int x, int y, int weight, string name = "null") {//从x节点到y节点，添加权重为weight，名字为name的事件
        assert(x < size);
        Matrix[x][y].weight = weight;
        Matrix[x][y].name = name;
    }
    int FirstNeighborOut(int u) {
        return NextNeighborOut(u, -1);
    }
    int NextNeighborOut(int u, int v) {//u节点指向相邻的v的下一个节点
        for (int i = v + 1; i < size; ++i) {
            if (Matrix[u][i].weight != INT_MAX) {
                return i;
            }
        }
        return -1;
    }
    vector<int> TopologicalSort() {//以队列形式排序
        vector<int> indegree((size_t)size);
        vector<int> order((size_t)size);
        queue<int> q;
        for (int i = 0; i < size; ++i) {
            indegree[i] = 0;
            order[i] = -1;
        }
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (Matrix[i][j].weight != INT_MAX) {
                    ++indegree[j];
                }
            }
        }

        for (int i = 0; i < size; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        int u;
        int count = 0;//记录已排序出队的个数
        while (!q.empty()) {//队列不为空继续循环
            u = order[count++] = q.front();
            q.pop();
            for (int p = this->FirstNeighborOut(u); p != -1; p = this->NextNeighborOut(u, p)) {//p遍历u的所有相邻节点
                if (!(--indegree[p])) {
                    q.push(p);
                }
            }
        }
        // for (int i = 0;i < size;++i) {
        //     cout << order[i] << " ";
        //     if (i != size - 1) {
        //         cout << Matrix[order[i]][order[i + 1]].name << " ";
        //     }
        // }
        // cout << endl;
        return order;
    }

    int FirstNeighborIn(int u) {//返回指向u的第一个节点
        return NextNeighborIn(u, -1);
    }
    int NextNeighborIn(int u, int v) {//返回指向u节点的下一个节点
        for (int i = v + 1; i < size; ++i) {
            if (Matrix[i][u].weight != INT_MAX) {
                return i;
            }
        }
        return -1;
    }
    vector<int> ReverseTopologicalSort() {//逆拓扑排序
        vector<int> outdegree(size);
        vector<int> order(size);
        queue<int> q;
        for (int i = 0; i < size; ++i) {
            outdegree[i] = 0;
            order[i] = -1;
        }
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (Matrix[i][j].weight != INT_MAX) {
                    ++outdegree[i];
                }
            }
        }

        for (int i = 0; i < size; ++i) {
            if (outdegree[i] == 0) {
                q.push(i);
            }
        }
        int u;
        int count = 0;//记录已排序出队的个数
        while (!q.empty()) {//队列不为空继续循环
            u = order[count++] = q.front();
            q.pop();
            for (int p = this->FirstNeighborIn(u); p != -1; p = this->NextNeighborIn(u, p)) {//p遍历u的所有相邻节点
                if (!(--outdegree[p])) {
                    q.push(p);
                }
            }
        }
        return order;
    }
    vector<int> CriticalPath() {//寻找图的关键路径
        vector<int> order = TopologicalSort();
        vector<int> ve(size);//ve为每个事件的最早发生时间 拓扑排序
        vector<int> vl(size);//vl为每个事件最晚发生的时间 使用逆拓扑排序
        ve[order[0]] = 0;//定义最开始的时间为0
        for (int i = 1;i < order.size();++i) {//从第二个事件开始
            int MaxWeight = 0;
            for (int p = FirstNeighborIn(order[i]);p != -1;p = NextNeighborIn(order[i], p)) {
                if (MaxWeight < ve[p] + Matrix[p][order[i]].weight) {
                    MaxWeight = ve[p] + Matrix[p][order[i]].weight;
                }
            }
            ve[order[i]] = MaxWeight;
        }
        vl[order[order.size() - 1]] = ve[order[order.size() - 1]];//汇点的ve == vl
        for (int i = order.size() - 2;i >= 0;--i) {
            int Min_Weight = INT_MAX;
            for (int p = FirstNeighborOut(order[i]);p != -1;p = NextNeighborOut(order[i], p)) {
                if (Min_Weight > vl[p] - Matrix[order[i]][p].weight) {
                    Min_Weight = vl[p] - Matrix[order[i]][p].weight;
                }
            }
            vl[order[i]] = Min_Weight;
        }
        vector<int> d(size);
        vector<int> critial_path;
        for (int i = 0;i < size;++i) {
            d[order[i]] = vl[order[i]] - ve[order[i]];
            if (d[order[i]] == 0) {
                critial_path.push_back(order[i]);
            }
        }
        return critial_path;
    }
};


int main() {
    AOEGraph* gr = new AOEGraph;
    AOEGraph g = *gr;
    for (int i = 0; i < 9; ++i) {
        g.InsertVertex();
    }
    // g.AddEdge(0, 1, 3);
    // g.AddEdge(0, 2, 2);
    // g.AddEdge(1, 3, 2);
    // g.AddEdge(2, 3, 4);
    // g.AddEdge(1, 4, 3);
    // g.AddEdge(3, 5, 2);
    // g.AddEdge(2, 5, 3);
    // g.AddEdge(4, 5, 1);
    g.AddEdge(0, 1, 6);
    g.AddEdge(1, 2, 1);
    g.AddEdge(2, 3, 9);
    g.AddEdge(3, 4, 2);
    g.AddEdge(0, 5, 1);
    g.AddEdge(5, 2, 1);
    g.AddEdge(2, 6, 8);
    g.AddEdge(6, 4, 4);
    g.AddEdge(5, 7, 4);
    g.AddEdge(0, 8, 5);
    g.AddEdge(8, 7, 2);
    g.AddEdge(7, 6, 4);
    print(g.CriticalPath());
    delete gr;
    return 0;
}