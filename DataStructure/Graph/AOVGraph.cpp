#include<iostream>
#include<vector>
#include<stack>
#include<assert.h>
#include<string>
#define MAX_SIZE 20
using namespace std;

class AOVGraph {//拓扑排序
    private:
    int Matrix[MAX_SIZE][MAX_SIZE];
    vector<string> Vertices;
    int size;
    public:
    AOVGraph() {
        for (int i = 0;i < MAX_SIZE;++i) {
            for (int j = 0;j < MAX_SIZE;++j) {
                Matrix[i][j] = 0;
            }
        }
        this->size = 0;
    }
    void AddVertex(string name) {
        Vertices.push_back(name);
        ++this->size;
    }
    void AddEdge(int x, int y) {
        assert(x < size && y < size && x >= 0 && y >= 0);
        Matrix[x][y] = 1;
    }
    int FirstArc(int x) {
        return NextArc(x, -1);
    }
    int NextArc(int x, int a) {
        for (int i = a+1;i < size;++i) {
            if (Matrix[x][i] != 0) {
                return i;
            }
        }
        return -1;
    }
    bool TopologicalSort() {
        stack<int> s;
        int indegree[size];
        int print[size];
        for (int i = 0;i < size;++i) {
            indegree[i] = 0;
        }
        for (int i = 0;i < size;++i) {
            for (int j = 0;j < size;++j) {
                if (Matrix[i][j]) {
                    ++indegree[j];//初始化数组
                }
            }
            print[i] = -1;
        }

        for (int i = 0;i < size;++i) {
            if (indegree[i] == 0) {
                s.push(i);
            }
        }
        int count = 0;
        int i;
        while (!s.empty()) {
            i = print[count++] = s.top();
            s.pop();
            for (int p = this->FirstArc(i);p != -1;p = this->NextArc(i, p)) {
                if (!(--indegree[p])) {
                    s.push(p);
                }
            }
        }
        for (int j = 0;j < size;++j) {
            cout << print[j] << " ";
        }
        if (count < size) {
            return false;
        } else {
            return true;
        }
    }
};

int main() {
    AOVGraph g;
    for (int i = 0;i < 5;++i) {
        g.AddVertex(string('A' + i, 1));
    }
    g.AddEdge(0, 1);
    g.AddEdge(1, 3);
    g.AddEdge(2, 3);
    g.AddEdge(2, 4);
    g.AddEdge(3, 4);
    g.AddEdge(0, 2);
    g.TopologicalSort();
    return 0;
}