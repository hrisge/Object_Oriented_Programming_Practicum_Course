#pragma once
#include <iostream>

class BigInt {
	char* number;
	bool isNegative;

	void copy(const BigInt&);
	void free();
	bool validNumber(const char*);
	static void trim(char*&);
	void resize(size_t capacity);
	void determineCarry(bool& carry, int& carrySign, char& sum) const;
	
public:
	BigInt();
	BigInt(const char*);
	BigInt(const BigInt&);
	BigInt& operator=(const BigInt&);
	~BigInt();
	BigInt abs() const;
	BigInt operator+(const BigInt&) const;
	BigInt operator-(const BigInt&) const;
	BigInt operator-() const;
	BigInt operator%(const BigInt&) const;
	BigInt operator/(const BigInt&) const;
	BigInt operator*(const BigInt&) const;
	BigInt& operator+=(const BigInt&);
	BigInt& operator-=(const BigInt&);
	BigInt& operator++();
	BigInt operator++(int);
	BigInt& operator--();
	BigInt operator--(int);
	bool operator==(const BigInt&) const;
	bool operator!=(const BigInt&) const;
	bool operator>(const BigInt&) const;
	bool operator<(const BigInt&) const;
	bool operator<=(const BigInt&) const;
	bool operator>=(const BigInt&) const;

	friend std::ostream& operator<<(std::ostream&, const BigInt&);
	friend std::istream& operator>>(std::istream&, BigInt&);
};