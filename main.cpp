
#include <iostream>

#include "matrix.h"

using namespace std;

int main(int argc, char *argv[]) {

    Matrix<int> a(4,4);
    Matrix<int> b(4,4);
    Matrix<int> c(4,4);

    for(int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            a.set(i, j, i+j);
        }
    }
    for(int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            b.set(i, j, 1);
        }
    }
    /*
    Matrix<int> d(2,2);
    d.set(0,1,2);
    d.printMatrix();
    cout << endl;
    (d.transposed()).printMatrix();
    cout << endl;
    d= d.transposed();
    d.printMatrix();
     */

    a.set(4, 4, 5);

    a.printMatrix();
    cout << endl;

    Matrix<int> e(4,1);
    for (int i =0; i<4; i++){
        e.set(i,0,1);
    }
    e.printMatrix();
    e= (a*e);
    cout << endl;
    e.printMatrix();

    system("PAUSE");
    return EXIT_SUCCESS;
}