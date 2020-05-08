#include <iostream>
using namespace std;

class Matrix {
public:
    Matrix(int row_i, int col_i):row(row_i),col(col_i) {
        new_mem();
    }
    ~Matrix() {
        for (int i = 0;i < row;i++) {
            delete[] content[i];
        }
        delete[] content;
    }
    Matrix(Matrix& copy){//一定要實作這個，不然函式回傳Matrix會出問題
        this->~Matrix();
        row = copy.row;
        col = copy.col;
        this->new_mem();
        for (int i = 0;i < row;i++) {
            for (int j = 0;j < col;j++) {
                content[i][j] = copy[i][j];
            }
        }
    }
    void new_mem() {
        if (content != nullptr) {
            this->~Matrix();
        }
        content = new int* [row] {};
        for (int i = 0;i < row;i++) {
            content[i] = new int[col] {};
        }
    }
    int* operator[](int index) {
        return content[index];
    }
    void print() {
        for (int i = 0;i < row;i++) {
            for (int j = 0;j < col;j++) {
                cout << content[i][j]<<' ';
            }
            cout << endl;
        }
    }
    void input() {
        for (int i = 0;i < row;i++) {
            for (int j = 0;j < col;j++) {
                cin >> content[i][j];
            }
        }
    }
    int row, col;
    int** content = nullptr;
};
Matrix Multiplication(Matrix& a, Matrix& b);
int main() {
    int rowA, rowB, colA, colB;
    while (cin >> rowA >> colA >> rowB >> colB) {
        Matrix matrixA(rowA,colA), matrixB(rowB,colB);
        matrixA.input();
        matrixB.input();
        if (matrixA.col != matrixB.row) {
            cout << "Matrix multiplication failed." << endl;
        }
        else {
            Multiplication(matrixA, matrixB).print();
        }
    }
    return 0;
}

Matrix Multiplication(Matrix& a,Matrix& b) {
    Matrix result(a.row, b.col);
    if (a.col != b.row) {
        return result;
    }
    for (int i = 0;i < a.row;i++) {
        for (int j = 0;j < b.col;j++) {
            for (int k = 0;k < a.col;k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}