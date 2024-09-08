#include <iostream>
#include <assert.h>
#include <random>
#include <time.h>
using namespace std;

class Symmetric_Matrix {
    private:
    int* data;
    int n; //存储行数和列数
    public:
    int getN() {
        return this->n;
    }
    Symmetric_Matrix(int x) {
        n = x;
        data = new int[n * (n + 1) / 2];
        for (int i = 0; i < n * (n + 1) / 2; ++i) {
            data[i] = 0;
        }
    }
    ~Symmetric_Matrix() {
        delete[] data;
    }
    class RowProxy {
        private:
        int* data_ptr;
        int row;
        int n;
        public:
        RowProxy(Symmetric_Matrix* matrix, int* data_ptr, int row) {
            this->row = row;
            n = matrix->getN();
            this->data_ptr = data_ptr;
        }
        int& operator[](int col) {
            assert(n > col && col >= 0);
            if (row < col) {
                int j = row;
                row = col;
                col = j;
            }
            return data_ptr[row * (row + 1) / 2 + col];
        }
    };
    RowProxy operator[](int row) {
        assert(n > row && row >= 0);
        return RowProxy(this, data, row);
    }
};

int main() {
    srand(time(NULL));
    Symmetric_Matrix m(5);
    for (int i = 0;i < 10;++i) {
        m[rand() % m.getN()][rand() % m.getN()] = rand() % 100;
    }
    for (int i = 0; i < m.getN(); ++i) {
        for (int j = 0; j < m.getN(); ++j) {
            cout << m[i][j] << "\t";
        }
        cout << endl;
        cout << endl;
    }
    return 0;
}