// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H
#define NEGSIZE ("Matrix size should be positive.")
#define MISIND ("Attempt to reach indices out of dimensions")
#define SAMESIZE ("Matrices are not equal sized.")
#define MULTSIZE ("Left matrix cols has to equal right matrix rows.")
#define STERR ("Stream error.")
#define TENTH (0.1)
#define TEN (10)
#include <iostream>

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
	int rows, cols;
} matrix_dims;

class Matrix
{
public:
    Matrix(int rows, int cols);
    Matrix();
    Matrix(const Matrix& m);
    ~Matrix();

    int get_rows() const;
    int get_cols() const;
    Matrix& transpose();
    Matrix& vectorize();
    void plain_print() const;
    Matrix dot(const Matrix& m) const;
    double norm() const;
    int argmax() const;
    float sum() const;
    Matrix operator+(const Matrix& rhs) const;
    Matrix& operator=(const Matrix& rhs);
    Matrix& operator+=(const Matrix& rhs);
    Matrix operator*(const Matrix& rhs) const;
    Matrix operator*(float rhs) const;
    friend Matrix operator*(float lhs,const Matrix& rhs);
    float operator()(int row, int col) const;
    float& operator()(int row, int col);
    float operator[](int k) const;
    float& operator[](int k);
    friend std::ostream& operator<<(std::ostream& out, const Matrix& m);
    friend std::istream& operator>>(std::istream& in, Matrix& m);
private:
    matrix_dims _dims;
    float** _data;

    bool samedims(const Matrix& rhs) const;
    void destroy();
};

#endif //MATRIX_H