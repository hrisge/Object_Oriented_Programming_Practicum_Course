#pragma once
#include "Integer.hpp"
#include "Integral.hpp"

class Rational : public Integral<Rational> {
    Integer nom;
    Integer denom;

    void simplify() ;

  public:
    Rational();
    Rational(Integer n);
    Rational(const Integer &nom, const Integer &denom);
    Rational operator+(const Rational &other) const override;
    Rational operator*(const Rational &other) const override;
    Rational operator-() const override;
    using Integral<Rational>::operator-;
    Rational operator/(const Rational &other) const override;
    bool lessThan(const Rational &other) const override;
    void serialize(std::ostream &out) const override;
} ;