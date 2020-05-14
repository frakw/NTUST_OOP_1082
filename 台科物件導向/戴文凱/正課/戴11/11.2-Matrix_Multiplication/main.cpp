#include <iostream>
#include "Matrix.h"
using namespace std;


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
