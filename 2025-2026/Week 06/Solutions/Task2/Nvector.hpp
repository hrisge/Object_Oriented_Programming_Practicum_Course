#pragma once
#include <functional>
#include <iostream>

class Nvector {
	size_t n;
	int* arr;
	void copy(const Nvector& other);
	void free();
	Nvector();
	// ще ни трябва помощна функция concat
	// по принцип помощните функции слагаме в private
	void concat(const Nvector& other);

public:
	Nvector(const int* arr, size_t n);
	Nvector(size_t n);
	Nvector(const Nvector& other);
	Nvector& operator=(const Nvector& other);
	~Nvector();
	Nvector operator+(const Nvector& other) const;
	Nvector operator-(const Nvector& other) const;
	Nvector operator*(int scalar) const;
	size_t size() const;
	int& operator[](size_t ind);
	const int& operator[](size_t ind) const;
	Nvector concatMap(std::function<Nvector(int)> f);
	friend std::ostream& operator<<(std::ostream& out, const Nvector& vec);
	friend std::istream& operator>>(std::istream& in, Nvector& vec);
};