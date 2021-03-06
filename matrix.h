#ifndef MATRIX_H
#define MATRIX_H

#include "node.h"
#include <iostream>
using namespace std;
template <typename T>
class Matrix {
private:
    Node<T> *hRows;
    Node<T> *hColumns;
    int columns;
    int rows;

public:
    Matrix() {
        hRows = nullptr;
        hColumns = nullptr;
        columns = 0;
        rows = 0;
    };

    Matrix(int sizeX, int sizeY) {
        rows = sizeX;
        columns = sizeY;

        Node<T> *tempColumn = new Node<T>;

        hColumns = tempColumn;


        tempColumn->y = 0;

        tempColumn->next = nullptr;
        tempColumn->down = nullptr;


        Node<T> *temp2Column = tempColumn;


        for (int i = 1; i < columns; i++) {
            tempColumn = new Node<T>;
            tempColumn->y = i;
            tempColumn->next = nullptr;
            tempColumn->down = nullptr;
            temp2Column->next = tempColumn;
            temp2Column = temp2Column->next;
        }

        Node<T> *tempRow = new Node<T>;
        tempRow->x = 0;
        tempRow->next = nullptr;
        tempRow->down = nullptr;
        hRows = tempRow;
        Node<T> *temp2Row = tempRow;

        for (int i = 1; i < rows; i++) {
            tempRow = new Node<T>;
            tempRow->x = i;

            tempRow->next = nullptr;
            tempRow->down = nullptr;
            temp2Row->down = tempRow;
            temp2Row = temp2Row->down;
        }


    };
    void printMatrix(){

        for (int i=0; i<rows; i++){
            for(int j=0; j<columns; j++){
                cout << operator()(i, j) << " ";
            }
            cout << endl;
        }

    };
    T operator()(int x, int y) {
        try {
            if (x >= rows || y >= columns) throw "Fuera de rango";

            auto tempRow = hRows;
            for (int i = 0; i < x; i++) {
                tempRow = tempRow->down;
            }

            tempRow = tempRow->next;

            while (tempRow != nullptr) {
                if (y == tempRow->y) {
                    return tempRow->data;
                } else {
                    tempRow = tempRow->next;
                }
            }
            return 0;
        } catch(const char* exception) {cout << "Error, " << exception << endl;}

    };

    void set(int x, int y, T data) {

        try {
            if (x >= rows || y >= columns) throw "Escapa del rango";
            auto tempRow = hRows;
            auto tempColumn = hColumns;
            Node<T> *tempElement = new Node<T>;
            tempElement->x = x;
            tempElement->y = y;
            tempElement->data = data;
            tempElement->next = nullptr;
            tempElement->down = nullptr;

            for (int i = 0; i < x; i++) {
                tempRow = tempRow->down;
            }
            for (int j = 0; j < y; j++) {
                tempColumn = tempColumn->next;
            }


            int flagReplace = 1;


            if (tempRow->next == nullptr) {
                tempRow->next = tempElement;
            } else {
                auto prev = tempRow;
                tempRow = tempRow->next;
                while (tempRow != nullptr) {
                    if (tempElement->y < tempRow->y) {
                        prev->next = tempElement;
                        tempElement->next = tempRow;
                        break;
                    } else {
                        if (tempElement->y == tempRow->y) {
                            tempRow->data = tempElement->data;
                            flagReplace = 0;
                            break;
                        }
                        prev = prev->next;
                        tempRow = tempRow->next;
                    }

                }
                if (tempRow == nullptr) {
                    prev->next = tempElement;
                    tempElement->next = tempRow;
                }
            }
            if (flagReplace) {
                if (tempColumn->down == nullptr) {
                    tempColumn->down = tempElement;
                } else {
                    auto prev = tempColumn;
                    tempColumn = tempColumn->down;
                    while (tempColumn != nullptr) {
                        if (tempElement->x < tempColumn->x) {
                            prev->down = tempElement;
                            tempElement->down = tempColumn;
                            break;
                        } else {
                            prev = prev->down;
                            tempColumn = tempColumn->down;
                        }
                    }
                    if (tempColumn == nullptr) {
                        prev->down = tempElement;
                        tempElement->down = tempColumn;
                    }
                }
            }
        } catch(const char* exception) {cout << "Error, " << exception << endl;}

    };




    Matrix<T>& operator*(Matrix<T> &other){
        try {
            if (columns != other.rows) throw "matrices no compatibles";
            T newElement;
            Matrix<T> *newMatrix = new Matrix<T>(rows, other.columns);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < other.columns; j++) {
                    newElement = 0;
                    for (int k = 0; k < columns; k++) {
                        newElement = newElement + ((this->operator()(i, k)) * (other.operator()(k, j)));
                    }
                    newMatrix->set(i, j, newElement);
                }
            }

            return *newMatrix;

        } catch (const char* error) {cout << "Error, " << error << endl;}

    };



    Matrix<T>& operator*(T scalar) {

        Matrix<T>* newMatrix= new Matrix<T>(rows, columns);
        auto tempRow= hRows;
        auto tempElement= tempRow;
        for (int i=0; i<rows; i++){
            tempElement= tempRow->next;
            while(tempElement!= nullptr){
                newMatrix->set(i, tempElement->y,(tempElement->data)*scalar );
                tempElement= tempElement->next;
            }
            tempRow= tempRow->down;
        }
        return *newMatrix;

    };
    Matrix<T>& operator+(Matrix<T>& other){

        try {
            if (rows != other.rows || columns != other.columns) throw "no son compatibles";
            Matrix<T> *newMatrix = new Matrix<T>(rows, columns);

            T newElement;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    newElement = operator()(i, j) + other(i, j);
                    if (newElement != 0) {
                        newMatrix->set(i, j, newElement);
                    }
                }
            }
            return *newMatrix;

        } catch (const char* error) {cout << "Error, " << error << endl;}

    };

    Matrix<T>& operator-(Matrix<T>& other){

        try {
            if (rows != other.rows || columns != other.columns) throw "no son compatibles";
                Matrix<T> *newMatrix = new Matrix<T>(rows, columns);
                T newElement;
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        newElement = operator()(i, j) - other(i, j);
                        if (newElement != 0) {
                            newMatrix->set(i, j, newElement);
                        }
                    }
                }
                return *newMatrix;
        } catch(const char* error) {cout << "Error, " << error << endl;}

    };

    Matrix<T>& transposed(){
        try {
            if (rows!= columns) throw "No es matriz cuadrada";
            Matrix<T> *newMatrix = new Matrix<T>(rows, columns);
            auto tempRow = hRows;
            auto tempElement = tempRow;
            for (int i = 0; i < rows; i++) {
                tempElement = tempRow->next;
                while (tempElement != nullptr) {
                    newMatrix->set(tempElement->y, i, tempElement->data);
                    tempElement = tempElement->next;
                }
                tempRow = tempRow->down;
            }
            this->operator=(*newMatrix);
            return *newMatrix;
        } catch(const char* error){ cout << error << endl; }
    };

    Matrix<T>& operator=(Matrix<T>& other){
        try
         {
            if(rows!= other.rows  || columns!=other.columns) throw "no son compatibles";
            T element;

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    element = other(i, j);
                    this->set(i, j, element);
                }

            }
            return *this;
        } catch (const char* error) {cout << error << endl;}
    };





    ~Matrix() {

        hColumns->killSelf();
        auto temp= hRows;
        auto temp2= temp;
        for (int i=0; i<rows; i++) {
            temp2= temp;
            temp= temp->down;
            temp2->killSelf();
        }
        delete temp;
    };


};

#endif