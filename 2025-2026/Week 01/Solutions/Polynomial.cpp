#include <iostream>

struct Term {
	double coefficient;
	double exponent;
};

const size_t MAX_TERMS = 128;

struct Polynomial {
	size_t size;
	Term terms[MAX_TERMS];
};

void printNum(double n) {
	if (n >= 0) std::cout << n;
	else std::cout << "(" << n << ")";
}

void printTerm(const Term& t) {
	printNum(t.coefficient);
	std::cout << "x^";
	printNum(t.exponent);
}

void print(const Polynomial& p) {
	for (size_t i = 0; i < p.size-1; i++) {
		printTerm(p.terms[i]);
		std::cout << " + ";
	}
	printTerm(p.terms[p.size - 1]);
	std::cout << std::endl;
}

bool hasCapacity(const Polynomial& p) {
	return p.size < MAX_TERMS;
}

void shiftRightFrom(Polynomial& p, size_t ind) {
	for (size_t i = p.size; i > ind; i--) {
		p.terms[i] = p.terms[i-1];
	}
}

void shiftLeftFrom(Polynomial& p, size_t ind) {
	for (size_t i = ind; i < p.size - 1; i++) {
		p.terms[i] = p.terms[i + 1];
	}
}

//работи подобно на алгоритъм за вмъкване в сортиран масив, като освен това се грижи за
//изразите с еднакви коефициенти и премахването на изрази с коефициент 0
void addTerm(Polynomial& p, const Term& t) {
	if (t.coefficient == 0) return;
	for (size_t i = 0; i < p.size; i++) {
		if (t.exponent > p.terms[i].exponent && hasCapacity(p)) {
			p.size++;
			shiftRightFrom(p, i);
			p.terms[i] = t;
			return;
		}
		else if (t.exponent == p.terms[i].exponent) {
			p.terms[i].coefficient += t.coefficient;
			if (p.terms[i].coefficient == 0) {
				shiftLeftFrom(p, i);
				p.size--;
			}
			return;
		}
	}
	if (hasCapacity(p)) {
		p.terms[p.size] = t;
		p.size++;
	}
}

Polynomial add(const Polynomial& p1, const Polynomial& p2) {
	Polynomial p = { 0, {} };
	for (size_t i = 0; i < p1.size; i++) {
		addTerm(p, p1.terms[i]);
	}
	for (size_t i = 0; i < p2.size; i++) {
		addTerm(p, p2.terms[i]);
	}
	return p;
}

Polynomial mult(const Polynomial& p1, const Polynomial& p2) {
	Polynomial p = { 0, {} };
	for (size_t j = 0; j < p2.size; j++) {
		for (size_t i = 0; i < p1.size; i++) {
			Term p1_i = p1.terms[i];
			Term p2_j = p2.terms[j];
			addTerm(p, { p1_i.coefficient * p2_j.coefficient, p1_i.exponent + p2_j.exponent });
		}
	}
	return p;
}

double eval(const Polynomial& p, double x) {
	double result = 0;
	for (size_t i = 0; i < p.size; i++) {
		result += p.terms[i].coefficient * pow(x, p.terms[i].exponent);
	}
	return result;
}