#include "sequence/ArraySequence.h"
#include <cmath>

template<typename T> class RectangleMatrix;

enum MatrixType {
    RECTANGLE,        
    SQUARE,           
    DIAGONAL,        
    UPPER_TRIANGLE,  
    LOWER_TRIANGLE,  
    SPARSE             
};

template<typename T>
class Matrix{
protected:
    void checkIndex(int i, int j) const {
        if (i < 0 || i >= rows || j < 0 || j >= columns) {
            throw std::invalid_argument("Index out of range");
        }
    }

    void checkNull(Matrix<T>* other) const{
        if(!other){
            throw std::invalid_argument("Null pointer");
        }
    }
protected:
    int rows, columns;
public:
    Matrix(int r, int c) : rows(r), columns(c) {}
    
    virtual T Get(int i, int j) = 0;
    virtual void Set(int i, int j, const T& value) = 0;
    virtual void Sum(Matrix<T>* other) = 0;
    virtual void Increase(const T& value) = 0;
    virtual double Norm() = 0;
    
    virtual void SwapRow(int first, int second) {throw std::logic_error("This type of matrix can`t do that");}
    virtual void IncreaseRow(int index, const T& value) {throw std::logic_error("This type of matrix can`t do that");}
    virtual void AddRow(int first, int second, const T& value) {throw std::logic_error("This type of matrix can`t do that");}
    virtual void SwapColumn(int first, int second) {throw std::logic_error("This type of matrix can`t do that");}
    virtual void IncreaseColumn(int index, const T& value) {throw std::logic_error("This type of matrix can`t do that");}
    virtual void AddColumn(int first, int second, const T& value) {throw std::logic_error("This type of matrix can`t do that");}

    virtual Matrix<T>* Transpose() {
        Matrix<T>* result = new RectangleMatrix<T>(this->columns, this->rows);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                result->Set(j, i, this->Get(i, j));
            }
        }
        return result;
    }

    virtual int Rank() {
        Matrix<T>* tmp = new RectangleMatrix<T>(this->rows, this->columns);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                tmp->Set(i, j, this->Get(i, j));
            }
        }

        int rank = std::min(this->rows, this->columns);
        
        for (int row = 0; row < rank; row++) {
            if (tmp->Get(row, row) == 0) {
                bool reduce = true;
                
                for (int i = row + 1; i < this->rows; i++) {
                    if (tmp->Get(i, row) != 0) {
                        tmp->SwapRow(row, i);
                        reduce = false;
                        break;
                    }
                }
                
                if (reduce) {
                    rank--;
                    continue;
                }
            }
            
            for (int i = row + 1; i < this->rows; i++) {
                T val = tmp->Get(i, row) / tmp->Get(row, row);
                for (int j = row; j < rank; ++j) {
                    T newVal = tmp->Get(i, j) - val * tmp->Get(row, j);
                    tmp->Set(i, j, newVal);
                }
            }
        }
        
        delete tmp;
        return rank;
    }

    virtual T Determinant(){
        Matrix<T>* tmp = new RectangleMatrix<T>(this->rows, this->columns);
        if (this->rows != this->columns) {
            throw std::logic_error("This type of matrix can`t do that");
        }
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                tmp->Set(i, j, this->Get(i, j));
            }
        }

        T det = 1;
        
        for (int i = 0; i < this->rows; i++) {
            if (tmp->Get(i, i) == 0) {
                int j;
                for (j = i + 1; j < this->rows; j++) {
                    if (tmp->Get(j, i) != 0) {
                        tmp->SwapRow(i, j);
                        det = -det;
                        break;
                    }
                }
                if (j == this->rows) {
                    delete tmp;
                    return 0;
                }
            }
            
            for (int j = i + 1; j < this->rows; j++) {
                T val = tmp->Get(j, i) / tmp->Get(i, i);
                for (int k = i; k < this->rows; k++) {
                    T newVal = tmp->Get(j, k) - val * tmp->Get(i, k);
                    tmp->Set(j, k, newVal);
                }
            }
            
            det *= tmp->Get(i, i);
        }
        
        delete tmp;
        return det;
    }

    int GetRows() const { return rows; }
    int GetColumns() const { return columns; }

    virtual ~Matrix() = default;
};

template <typename T>
class RectangleMatrix: public Matrix<T>{
private:
    MutableArraySequence<MutableArraySequence<T>*>* data;
public:
    RectangleMatrix(int new_column, int new_row): Matrix<T>(new_column, new_row){
        MutableArraySequence<MutableArraySequence<T>*>*new_data = new MutableArraySequence<MutableArraySequence<T>*>();
        for(int i = 0; i < new_row; i++){
            T* fictive = new T[new_column];
            MutableArraySequence<T>* new_row = new MutableArraySequence<T>(fictive,this->columns);
            new_data->Append(new_row);
            delete fictive;
        }
        data = new_data;
    }

    void Set(int row, int column, const T& value) override{
        this->checkIndex(row, column);

        data->Get(row)->Set(column, value);
    }

    T Get(int row, int column) override{
        this->checkIndex(row, column);

        return data->Get(row)->Get(column);
    }

    void Sum(Matrix<T>* other) override{
        this->checkIndex(other->GetRows(), other->GetColumns());
        this->checkNull(other);

        for(int i = 0; i < this->rows; i++){
            for(int j = 0; j < this->columns; j++){
                T sum_value = this->Get(i, j) + other->Get(i, j);
                this->Set(i, j, sum_value);
            }
        }
    }

    void Increase(const T& value) override{
        for(int i = 0; i < this->rows; i++){
            for(int j = 0; j < this->columns; j++){
                this->Set(i, j, this->Get(i, j) * value);
            }
        }
    }

    double Norm() override{
        double ans = 0;
        for(int i = 0; i < this->rows; i++){
            for(int j = 0; j < this->columns; j++){
                ans += this->Get(i, j) * this->Get(i,j);
            }
        }
        return sqrt(ans);
    }

    void SwapRow(int first, int second) override{
        if(first < 0 || first >= this->rows || second < 0 || second >= this->rows){ throw std::invalid_argument("Index out of range");}

        MutableArraySequence<T> *row = data->Get(first);
        data->Set(first, data->Get(second));
        data->Set(second, row);
    }

    void SwapColumn(int first, int second) override{
        if(first < 0 || first >= this->columns || second < 0 || second >= this->columns){ throw std::invalid_argument("Index out of range");}

        for(int i = 0; i < this->rows; i++){
            T value = this->Get(i, first);
            this->Set(i, first, this->Get(i, second));
            this->Set(i, second, value);
        }
    }

    void IncreaseRow(int index, const T& value) override{
        if(index < 0 || index >= this->rows ){ throw std::invalid_argument("Index out of range");}

        for(int i = 0; i < this->columns; i++){
            this->Set(index, i, this->Get(index, i) * value);
        }
    }

    void IncreaseColumn(int index, const T& value) override{
        if(index < 0 || index >= this->columns ){ throw std::invalid_argument("Index out of range");}

        for(int i = 0; i < this->rows; i++){
            this->Set(i, index, this->Get(i, index) * value);
        }
    }

    void AddRow(int first, int second, const T& value) override{
        if(first < 0 || first >= this->rows || second < 0 || second >= this->rows){ throw std::invalid_argument("Index out of range");}

        for(int i = 0;i < this->columns; i++){
            this->Set(first, i, this->Get(second, i) * value + this->Get(first, i));
        }
    }

    void AddColumn(int first, int second, const T& value) override{
        if(first < 0 || first >= this->columns || second < 0 || second >= this->columns){ throw std::invalid_argument("Index out of range");}

        for(int i = 0;i < this->rows; i++){
            this->Set(i, first, this->Get(i, second) * value + this->Get(i, first));
        }
    }

    ~RectangleMatrix(){
        for(int i = 0;  i < this->rows; i++){
            delete data->Get(i);
        }
        delete data;
    }
};

template<typename T>
class SquareMatrix: public RectangleMatrix<T>{
public:
    SquareMatrix(int n) : RectangleMatrix<T>(n, n) {}
};

template<typename T>
class DiagMatrix : public Matrix<T> {
    MutableArraySequence<T>* data;

public:
    DiagMatrix(int n) : Matrix<T>(n, n) {
        T *values = new T[n]();
        data = new MutableArraySequence<T>(values, n);
    }

    T Get(int i, int j) override {
        this->checkIndex(i, j);

        return (i == j) ? data->Get(i) : 0;
    }

    void Set(int i, int j, const T& value) override {
        this->checkIndex(i, j);

        if (i != j){return;}
        data->Set(i, value);
    }

    void Sum(Matrix<T>* other) override {
        this->checkIndex(other->GetRows(), other->GetColumns());
        this->checkNull(other);

        for (int i = 0; i < this->rows; ++i) {
            this->Set(i, i, this->Get(i, i) + other->Get(i, i));
        }
    }

    void Increase(const T& value) override {
        for (int i = 0; i < this->rows; ++i) {
            this->Set(i, i, this->Get(i, i) * value);
        }
    }

    double Norm() override {
        double ans = 0;
        for (int i = 0; i < this->rows; ++i) {
            T val = this->Get(i, i);
            ans += sqrt(val * val);
        }
        return sqrt(ans);
    }

    T Determinant() override {
        T det = 1;
        for (int i = 0; i < this->rows; ++i) {
            det *= this->Get(i, i);
        }
        return det;
    }

    Matrix<T>* Transpose() {
        DiagMatrix<T>* result = new DiagMatrix<T>(this->rows);
        for (int i = 0; i < this->rows; ++i) {
            result->Set(i, i, this->Get(i, i));
        }
        return result;
    }

    ~DiagMatrix(){delete data;}
};

template <typename T>
class TriangleMatrix : public Matrix<T> {
protected:
    bool isUpper; 
    MutableArraySequence<T>* data;

    int getIndex(int i, int j) {
        if (isUpper) {
            if (i > j) return -1; 
            return  j + i * (i + 1) / 2;
        } else {
            if (i < j) return -1; 
            return i + j * (j + 1) / 2;
        }
    }

public:
    TriangleMatrix(int size, bool upper): Matrix<T>(size, size), isUpper(upper){
        T *values = new T[size * (size + 1) / 2]();
        data = new MutableArraySequence<T>(values, size * (size + 1) / 2);
    }

    T Get(int i, int j) override {
        this->checkIndex(i, j);

        int ind = getIndex(i, j);
        if (ind == -1) return 0;
        return data->Get(ind);
    }

    void Set(int i, int j, const T& value) override {
        this->checkIndex(i, j);

        int ind = getIndex(i, j);
        if (ind == -1) {
            return;
        }
        data->Set(ind, value);
    }

    void Sum(Matrix<T>* other) override {
        this->checkIndex(other->GetRows(), other->GetColumns());
        this->checkNull(other);

        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                this->Set(i, j, this->Get(i, j) + other->Get(i, j));
            }
        }
    }

    void Increase(const T& value) override {
        for (int i = 0; i < data->GetLength(); ++i) {
            data->Set(i, data->Get(i) * value);
        }
    }

    double Norm() override {
        double ans = 0;
        for (int i = 0; i < this->rows; ++i) {
            T val = this->Get(i, i);
            ans += sqrt(val * val);
        }
        return sqrt(ans);
    }

    bool IsUpper() { return isUpper; }

    T Determinant() override {
        T det = 1;
        for (int i = 0; i < this->rows; ++i) {
            det *= this->Get(i, i);
        }
        return det;
    }
    
    ~TriangleMatrix() {delete data;}
};

template<typename T>
class SparseMatrix: public Matrix<T>{
private:
    MutableArraySequence<MutableArraySequence<std::pair<int, T>*>*>* data;

    int getIndex(int i, int j){
        for(int ind = 0; ind < data->Get(i)->GetLength();ind++){
            if(data->Get(i)->Get(ind)->first == j){
                return ind;
            }
        }
        return -1;
    }
public:
    SparseMatrix(int c, int r): Matrix<T>(c, r){
        data = new MutableArraySequence<MutableArraySequence<std::pair<int,T>*>*>();
        for(int i = 0; i < r; i++){
            data->Append(new MutableArraySequence<std::pair<int, T>*>);
        }
    }

    T Get(int i, int j) override{
        this->checkIndex(i, j);

        int ind = getIndex(i, j);
        if(ind == -1){
            return 0;
        }
        return data->Get(i)->Get(ind)->second;
    }

    void Set(int i, int j, const T& value) override{
        this->checkIndex(i, j);

        int ind = getIndex(i, j);
        std::pair<int, T> * pair = new std::pair<int, T>(j, value);
        if(ind == -1){
            data->Get(i)->Append(pair);
        }
        else{
            data->Get(i)->Set(ind, pair);
        }
    }

    void Sum(Matrix<T>* other) override{
        this->checkIndex(other->GetRows(), other->GetColumns());
        this->checkNull(other);
        
        for(int i = 0; i < other->GetRows(); i++){
            for(int j = 0; j < other->GetColumns(); j++){
                this->Set(i, j, other->Get(i, j) + this->Get(i, j));
            }
        }
    }

    void Increase(const T& value) override{
        for(int i = 0; i < this->rows; i++){
            for(int j = 0; j < data->Get(i)->GetLength();j++){
                this->Set(i, data->Get(i)->Get(j)->first, data->Get(i)->Get(j)->second * value);
            }
        }
    }

    double Norm() override{
        double ans = 0;
        for(int i = 0; i < this->rows; i++){
            for(int j = 0; j < data->Get(i)->GetLength(); j++){
                T val = data->Get(i)->Get(j)->second;
                ans += val * val;
            }
        }
        return sqrt(ans);
    }

    ~SparseMatrix(){
        for(int i = 0; i < data->GetLength();i++){
            for(int j = 0; j < data->Get(i)->GetLength(); j++){
                delete data->Get(i)->Get(j);
            }
            delete data->Get(i);
        }

        delete data;
    }
};


template<typename T>
void printMatrix(Matrix<T>* mat){
    for(int i = 0; i < mat->GetRows(); i++){
        for(int j = 0; j < mat->GetColumns(); j++){
            std::cout << mat->Get(i, j) << " ";
        }
        std::cout << "\n";
    }
}


template<typename T>
Matrix<T>* ConvertMatrix(Matrix<T>* mat, MatrixType type) {
    int rows = mat->GetRows();
    int cols = mat->GetColumns();
    
    switch(type) {
        case SQUARE:
        case DIAGONAL:
        case UPPER_TRIANGLE:
        case LOWER_TRIANGLE:
            if(rows != cols) {
                throw std::invalid_argument("Need square matrix");
            }
            break;
        default:
            break;
    }
    
    Matrix<T>* result;
    switch(type) {
        case RECTANGLE:
            result = new RectangleMatrix<T>(rows, cols);
            break;
        case SQUARE:
            result = new SquareMatrix<T>(rows);
            break;
        case DIAGONAL:
            result = new DiagMatrix<T>(rows);
            break;
        case UPPER_TRIANGLE:
            result = new TriangleMatrix<T>(rows, true);
            break;
        case LOWER_TRIANGLE:
            result = new TriangleMatrix<T>(rows, false);
            break;
        case SPARSE:
            result = new SparseMatrix<T>(rows, cols);
            break;
        default:
            throw std::invalid_argument("Unknown matrix type");
    }
    
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            T value = mat->Get(i, j);
            
            if(type == DIAGONAL && i != j) {
                continue;
            }
            
            if(type == UPPER_TRIANGLE && i > j) {
                continue;
            }
            
            if(type == LOWER_TRIANGLE && i < j) {
                continue;
            }
            
            if(type == SPARSE && value == 0) {
                continue;
            }
            
            result->Set(i, j, value);
        }
    }
    
    return result;
}