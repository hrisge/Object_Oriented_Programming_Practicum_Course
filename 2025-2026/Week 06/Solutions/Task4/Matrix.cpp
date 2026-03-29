#include "Matrix.hpp"

void Matrix::copy(const Matrix& other)
{
    rows = other.rows;
    cols = other.cols;
    allocate();
}

void Matrix::free()
{
    for (size_t i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void Matrix::allocate()
{
    matrix = new int* [rows];
    for (size_t i = 0; i < rows; i++) {
        matrix[i] = new int[cols] {0};
    }
}

void Matrix::map(const std::function<int(int i, int j)> f)
{
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            matrix[i][j] = f(i, j);
        }
    }
}

bool Matrix::any(const std::function<bool(int i, int j)> f) const
{
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (f(i, j)) return true;
        }
    }
    return false;
}

Matrix::Matrix() : rows(2), cols(2)
{
    allocate();
}

Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols)
{
    allocate();
}

Matrix::Matrix(const Matrix& other)
{
    copy(other);
}

Matrix& Matrix::operator=(const Matrix& other)
{
    if (this == &other) return *this;
    free();
    copy(other);
    return *this;
}

Matrix::~Matrix()
{
    free();
}

Matrix& Matrix::operator+=(const Matrix& other)
{
    if (rows != other.rows || cols != other.cols) return *this;
    map([this, &other](int i, int j) {return matrix[i][j] + other[i][j]; });
}

Matrix Matrix::operator+(const Matrix& other) const
{
    if (rows != other.rows || cols != other.cols) return Matrix();
    Matrix result = *this;
    return result += other;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
    if (rows != other.rows || cols != other.cols) return *this;
    map([this, &other](int i, int j) {return matrix[i][j] - other[i][j]; });
}

Matrix Matrix::operator-(const Matrix& other) const
{
    if (rows != other.rows || cols != other.cols) return Matrix();
    Matrix result = *this;
    return result -= other;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
    if (this->cols != other.rows) return *this;
    *this = *this * other;
    return *this;
    
}

Matrix Matrix::operator*(const Matrix& other)
{
    if (this->cols != other.rows) return Matrix();
    Matrix result(rows, other.cols);
    // всеки елемент M[i][j] в резултата е равен на скаларното произведение
    // на ред i на първата матрица със стълб j на втората
    result.map([this, &other](int i, int j) {
            int dotProduct = 0;
            for (size_t k = 0; k < cols; k++) {
                dotProduct += matrix[i][k] * other[k][j];
            }
            return dotProduct;
        });
    return result;
}

Matrix& Matrix::operator*=(int number)
{
    map([this, &number](int i, int j) {return matrix[i][j]*number; });
}

Matrix Matrix::operator*(int number) const
{
    Matrix result = *this;
    return result *= number;
}

bool Matrix::operator==(const Matrix& other) const
{
   return !any([this, &other](int i, int j) {return matrix[i][j] != other[i][j];});
}

bool Matrix::operator!=(const Matrix& other) const
{
    return any([this, &other](int i, int j) {return matrix[i][j] != other[i][j];});
}

int*& Matrix::operator[](size_t row)
{
    return matrix[row];
}

const int*& const Matrix::operator[](size_t row) const
{
    return matrix[row];
}
