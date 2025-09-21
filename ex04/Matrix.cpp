#include "Matrix.h"
#include <cmath>
Matrix::Matrix(int rows, int cols): _dims{rows,cols}{
    if(rows <= 0 || cols <= 0){
        throw std::length_error(NEGSIZE);
    }
    _data = new float* [rows];
    for(int i = 0;i<rows;i++){
        _data[i] = new float [cols];
        for(int k = 0;k<cols;k++){
            _data[i][k] = 0;
        }
    }
}

Matrix::Matrix(): Matrix(1,1) {
}

Matrix::Matrix(const Matrix& m): Matrix{m._dims.rows, m._dims.cols}{
    for(int i = 0; i<_dims.rows; i++)
    {
        for(int k=0; k<_dims.cols; k++)
        {
            _data[i][k] = m._data[i][k];
        }
    }
}

Matrix::~Matrix(){
    for(int i = 0; i<_dims.rows ; i++){
            delete[] _data[i];
    }
    delete[] _data;
}

int Matrix::get_rows() const{
    return _dims.rows;
}

int Matrix::get_cols() const{
    return _dims.cols;
}

Matrix& Matrix::transpose(){
    Matrix tr(_dims.cols, _dims.rows);
    for(int i=0; i<_dims.rows; i++){
        for(int k=0; k<_dims.cols; k++){
            tr._data[k][i] = _data[i][k];
        }
    }
    (*this) = tr;
    return (*this);
}

Matrix& Matrix::vectorize(){
    Matrix vr(_dims.rows * _dims.cols, 1);
    for(int i = 0; i<vr._dims.rows;i++){
        vr[i] = (*this)[i];
    }
    (*this) = vr;
    return (*this);
}

void Matrix::plain_print() const{
    for(int i=0; i<_dims.rows; i++){
        for(int k=0; k<_dims.cols; k++){
            std::cout << _data[i][k] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::dot(const Matrix &m) const{
    if(!samedims(m)){
        throw std::length_error(SAMESIZE);
    }
    Matrix dm= Matrix(_dims.rows, _dims.cols);
    for(int i=0; i<_dims.rows; i++){
        for(int k=0; k<_dims.cols; k++){
            dm._data[i][k] = _data[i][k] * m._data[i][k];
        }
    }
    return dm;
}

double Matrix::norm() const{
    double fnorm = 0;
    for(int i=0; i<_dims.rows; i++){
        for(int k=0; k<_dims.cols; k++){
            fnorm+= pow(_data[i][k],2);
        }
    }
    return sqrt(fnorm);
}

int Matrix::argmax() const{
    float maxval = _data[0][0];
    int maxind = 0;
    for(int i=0; i<_dims.rows; i++){
        for(int k=0; k<_dims.cols; k++){
            if (_data[i][k] > maxval){
                maxval = _data[i][k];
                maxind = i*_dims.cols + k;
            }
        }
    }
    return maxind;
}

float Matrix::sum() const{
    float sum=0;
    for(int i=0; i<_dims.rows; i++){
        for(int k=0; k<_dims.cols; k++){
            sum+=_data[i][k];
        }
    }
    return sum;
}

Matrix Matrix::operator+(const Matrix& rhs) const{
    if(!samedims(rhs)){
        throw std::length_error(SAMESIZE);
    }
    Matrix added = Matrix(_dims.rows, _dims.cols);
    for(int i=0; i<added._dims.rows; i++){
        for(int k=0; k<added._dims.cols; k++){
            added._data[i][k] = _data[i][k] + rhs._data[i][k];
        }
    }
    return added;
}

bool Matrix::samedims(const Matrix &rhs) const{
    return (_dims.rows == rhs._dims.rows && _dims.cols == rhs._dims.cols);
}

void Matrix::destroy(){
    for(int i=0; i<_dims.rows; i++){
        delete[] _data[i];
    }
    delete[] _data;
}

Matrix& Matrix::operator=(const Matrix& rhs){
    if(this == &rhs){
        return (*this);
    }
    if(!samedims(rhs)){
        destroy();
        _dims.rows = rhs._dims.rows;
        _dims.cols = rhs._dims.cols;
        _data = new float* [_dims.rows];
        for(int i = 0; i<_dims.rows; i++){
            _data[i] = new float[_dims.cols];
        }
    }
    for(int i=0; i<_dims.rows; i++){
        for(int k=0; k<_dims.cols; k++){
            _data[i][k] = rhs._data[i][k];
        }
    }
    return (*this);
}

Matrix& Matrix::operator+=(const Matrix &rhs){
    if(!samedims(rhs)){
        throw std::length_error(SAMESIZE);
    }
    for(int i=0; i<_dims.rows; i++){
        for(int k=0; k<_dims.cols; k++){
            _data[i][k] += rhs._data[i][k];
        }
    }
    return (*this);
}

Matrix Matrix::operator*(const Matrix& rhs) const{
    if(_dims.cols!=rhs._dims.rows){
        throw std::length_error(MULTSIZE);
    }
    Matrix mult = Matrix(_dims.rows,rhs._dims.cols);
    for(int i=0; i< _dims.rows; i++){
        for(int k = 0; k< rhs._dims.cols ; k++){
            for(int l= 0; l< rhs._dims.rows ; l++){
                mult._data[i][k] += _data[i][l] * rhs._data[l][k];
            }
        }
    }
    return mult;
}

Matrix Matrix::operator*(float rhs) const{
    Matrix mult = *this;
    for(int i=0; i<_dims.rows; i++){
        for(int k=0; k<_dims.cols; k++){
            mult._data[i][k] *= rhs;
        }
    }
    return mult;
}

Matrix operator*(float lhs,const Matrix& rhs){
    return rhs*lhs;
}

float Matrix::operator()(int row, int col) const{
    if(_dims.rows < row || _dims.cols < col){
        throw std::length_error(MISIND);
    }
    if(_dims.rows <= 0 || _dims.cols <= 0){
        throw std::length_error(NEGSIZE);
    }
    return _data[row][col];
}

float& Matrix::operator()(int row, int col){
    if(_dims.rows < row || _dims.cols < col){
        throw std::length_error(MISIND);
    }
    if(_dims.rows <= 0 || _dims.cols <= 0){
        throw std::length_error(NEGSIZE);
    }
    return _data[row][col];
}

float Matrix::operator[](int k) const{
    if(k>_dims.rows * _dims.cols){
        throw std::length_error(MISIND);
    }
    int row = k/_dims.cols;
    int col = k%_dims.cols;
    return _data[row][col];
}

float& Matrix::operator[](int k){
    if(k>_dims.rows * _dims.cols){
        throw std::length_error(MISIND);
    }
    int row = k/_dims.cols;
    int col = k%_dims.cols;
    return _data[row][col];
}

std::ostream& operator<<(std::ostream& out, const Matrix& m){
    if(!out){
        throw std::length_error(STERR);
    }
    for(int i=0; i<m._dims.rows; i++){
        for(int k=0; k<m._dims.cols; k++){
            if(m(i,k) > TENTH){
                out << "**";
            }
            else{
                out << "  ";
            }
        }
        out << std::endl;
    }
    return out;
}

std::istream& operator>>(std::istream& in, Matrix& m){
    if(!in){
        throw std::length_error(STERR);
    }
    in.seekg(0, std::istream::end);
    int length = in.tellg();
    if((int)(length/sizeof(int)) < (m._dims.rows * m._dims.cols)){
        throw std::length_error(STERR);
    }
    in.seekg(std::istream::beg);
    char* buffer = new char [length];
    in.read(buffer, length);
    auto* rec = (float*) buffer;
    for(int i=0; i<m._dims.rows * m._dims.cols; i++){
            m[i] = rec[i];
    }
    delete[] buffer;
    return in;
}
