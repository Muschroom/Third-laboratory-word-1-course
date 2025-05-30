#include <iostream>
#include <limits>
#include "headers/Matrix.h"

using namespace std;

int selectDataType() {
    cout << "\nSelect data type:" << endl;
    cout << "1. int" << endl;
    cout << "2. double" << endl;
    cout << "0. Exit" << endl;
    
    int choice;
    cin >> choice;
    return choice;
}

int selectMatrixType() {
    cout << "\nMatrix type:" << endl;
    cout << "1. Rectangle" << endl;
    cout << "2. Square" << endl;
    cout << "3. Diagonal" << endl;
    cout << "4. Upper Triangle" << endl;
    cout << "5. Lower Triangle" << endl;
    cout << "6. Sparse" << endl;
    cout << "0. Exit" << endl;
    
    int choice;
    cin >> choice;
    return choice;
}

template<typename T>
Matrix<T>* createMatrix(int type) {
    int rows, cols;
    cout << "Number of rows: ";
    cin >> rows;
    
    if (type != 2 && type != 3 && type != 4 && type != 5) {
        cout << "Number of columns: ";
        cin >> cols;
    } else {
        cols = rows; 
    }

    switch (type) {
        case 1: return new RectangleMatrix<T>(rows, cols);
        case 2: return new SquareMatrix<T>(rows);
        case 3: return new DiagMatrix<T>(rows);
        case 4: return new TriangleMatrix<T>(rows, true);
        case 5: return new TriangleMatrix<T>(rows, false);
        case 6: return new SparseMatrix<T>(rows, cols);
        default: return nullptr;
    }
}

template<typename T>
void fillMatrix(Matrix<T>* mat) {
    cout << "\nFill matrix:" << endl;
    for (int i = 0; i < mat->GetRows(); i++) {
        for (int j = 0; j < mat->GetColumns(); j++) {
            T value;
            cout << "Element [" << i << "][" << j << "]: ";
            cin >> value;
            mat->Set(i, j, value);
        }
    }
}

int selectOperation() {
    cout << "\nOperation:" << endl;
    cout << "1. Print matrix" << endl;
    cout << "2. Increase" << endl;
    cout << "3. Transpose" << endl;
    cout << "4. Determinant" << endl;
    cout << "5. Rank" << endl;
    cout << "6. SwapRow" << endl;
    cout << "7. SwapColumn" << endl;
    cout << "8. Convert" << endl;
    cout << "0. Exit" << endl;
    
    int choice;
    cin >> choice;
    return choice;
}

template<typename T>
void performOperation(Matrix<T>* mat) {
    while (true) {
        int op = selectOperation();
        if (op == 0) break;

        switch (op) {
            case 1:
                cout << "\nMatrix:" << endl;
                printMatrix(mat);
                break;
                
            case 2: { 
                T value;
                cout << "Number: ";
                cin >> value;
                mat->Increase(value);
                cout << "Result:" << endl;
                printMatrix(mat);
                break;
            }
                
            case 3: { 
                try {
                    Matrix<T>* transposed = mat->Transpose();
                    cout << "\nTransposed matrix:" << endl;
                    printMatrix(transposed);
                    delete transposed;
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
                
            case 4: {
                try {
                    T det = mat->Determinant();
                    cout << "Determinant = " << det << endl;
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
                
            case 5: {
                try {
                    int rank = mat->Rank();
                    cout << "Rank = " << rank << endl;
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
                
            case 6: { 
                int row1, row2;
                cout << "Row indices: ";
                cin >> row1 >> row2;
                try {
                    mat->SwapRow(row1, row2);
                    cout << "Rows " << row1 << " and " << row2 << " swapped." << endl;
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
                
            case 7: { 
                int col1, col2;
                cout << "Column indices: ";
                cin >> col1 >> col2;
                try {
                    mat->SwapColumn(col1, col2);
                    cout << "Columns " << col1 << " and " << col2 << " swapped." << endl;
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
                
            case 8: { 
                cout << "\nMatrix type:" << endl;
                cout << "1. Rectangle" << endl;
                cout << "2. Square" << endl;
                cout << "3. Diagonal" << endl;
                cout << "4. Upper Triangle" << endl;
                cout << "5. Lower Triangle" << endl;
                cout << "6. Sparse" << endl;
                cout << "0. Exit" << endl;
    
                int newType;
                cin >> newType;
                
                MatrixType targetType;
                switch (newType) {
                    case 1: targetType = RECTANGLE; break;
                    case 2: targetType = SQUARE; break;
                    case 3: targetType = DIAGONAL; break;
                    case 4: targetType = UPPER_TRIANGLE; break;
                    case 5: targetType = LOWER_TRIANGLE; break;
                    case 6: targetType = SPARSE; break;
                    default: {
                        cout << "Invalid choice" << endl;
                        continue;
                    }
                }
                
                try {
                    Matrix<T>* converted = ConvertMatrix(mat, targetType);
                    cout << "\nConverted matrix:" << endl;
                    printMatrix(converted);
                    delete converted;
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
                
            default:
                cout << "Invalid choice" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void handleMatrixCreation(int type) {
    int dataType = selectDataType();
    if (dataType == 0) return;

    switch (dataType) {
        case 1: {
            Matrix<int>* intMatrix = createMatrix<int>(type);
            if (!intMatrix) {
                cout << "Invalid choice" << endl;
                return;
            }
            fillMatrix(intMatrix);
            performOperation(intMatrix);
            delete intMatrix;
            break;
        }
        case 2: {
            Matrix<double>* doubleMatrix = createMatrix<double>(type);
            if (!doubleMatrix) {
                cout << "Invalid choice" << endl;
                return;
            }
            fillMatrix(doubleMatrix);
            performOperation(doubleMatrix);
            delete doubleMatrix;
            break;
        }
        default:
            cout << "Invalid choice" << endl;
    }
}

int main() {
    while (true) {
        int type = selectMatrixType();
        if (type == 0) break;

        handleMatrixCreation(type);
    }

    return 0;
}