#include "Rational.hpp"

void Rational::simplify() {
        if(nom == Integer(0)){
            denom = 1;
            return;
        }
        Integer gcd = nom.gcd(denom);
        nom = nom/gcd;
        denom = denom/gcd;
}
Rational::Rational() : nom(0), denom(1) {}
Rational::Rational(Integer n) : nom(n), denom(1) {}
Rational::Rational(const Integer &nom, const Integer &denom)
    : nom(nom), denom(denom) {
  if (denom == Integer(0))
    throw std::runtime_error("division by zero");
  simplify();
}
Rational Rational::operator+(const Rational &other) const {
  Integer resultNom = nom * other.denom + other.nom * denom;
  Integer resultDenom = denom * other.denom;
  Rational result(resultNom, resultDenom);
  result.simplify();
  return result;
}
Rational Rational::operator*(const Rational &other) const {
  Rational result(nom * other.nom, denom * other.denom);
  result.simplify();
  return result;
}
Rational Rational::operator-() const { return Rational(-nom, denom); }
Rational Rational::operator/(const Rational &other) const {
  Rational result = *this * Rational(other.denom, other.nom);
  result.simplify();
  return result;
}
bool Rational::lessThan(const Rational &other) const {
  Integer nom1 = nom * other.denom;
  Integer nom2 = other.nom * denom;
  return nom1 < nom2;
}
void Rational::serialize(std::ostream &out) const {
  if (denom == Integer(1)) {
    out << nom;
    return;
  }
  out << nom << "/" << denom;
}
