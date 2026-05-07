#pragma once
#include "Array.hpp"
#include "Integral.hpp"
#include "Rational.hpp"

class Polynomial : public Integral<Polynomial> {
    struct Term{
        Rational coefficient;
        size_t exponent;
    };
    Array<Term> terms;
    void shiftRightFrom(size_t ind) ;
    void shiftLeftFrom(size_t ind);
    void addTerm(const Term &t);
    Polynomial(const Array<Term> &arr);

  public:
    Polynomial() = default;
    Polynomial(int n) {
        addTerm({Rational(n), 0});
    }
    Polynomial(const Rational &coefficient, unsigned exponent);
    Polynomial operator+(const Polynomial &other) const override;
    Polynomial operator*(const Polynomial &other) const override;
    Polynomial operator-() const override;
    using Integral<Polynomial>::operator-;
    Polynomial operator/(const Polynomial &other) const override;
    long long degree() const;
    bool lessThan(const Polynomial &other) const override;
    void serialize(std::ostream &out) const override;
};