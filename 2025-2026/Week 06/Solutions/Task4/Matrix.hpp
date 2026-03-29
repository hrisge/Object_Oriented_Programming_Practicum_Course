#pragma once
#include <functional>
class Matrix {
	size_t rows;
	size_t cols;
	int** matrix;
	void copy(const Matrix& other);
	void free();
	void allocate();
	//почти всичко в тази задача се решава на 2-3 реда с подходящ map ;D
	void map(const std::function<int(int i, int j)> f);
	bool any(const std::function<bool(int i, int j)> f) const;
public:
	Matrix();
	Matrix(size_t rows, size_t cols);
	Matrix(const Matrix& other);
	Matrix& operator=(const Matrix& other);
	~Matrix();
	Matrix& operator+=(const Matrix& other);
	Matrix operator+(const Matrix& other) const;
	Matrix& operator-=(const Matrix& other);
	Matrix operator-(const Matrix& other) const;
	Matrix& operator*=(const Matrix& other);
	Matrix operator*(const Matrix& other);
	Matrix& operator*=(int number);
	Matrix operator*(int number) const;
	bool operator==(const Matrix& other) const;
	bool operator!=(const Matrix& other) const;
	int*& operator[](size_t row);
	const int*& const operator[] (size_t row) const;
};


