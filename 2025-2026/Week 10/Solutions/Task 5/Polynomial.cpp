#include "Polynomial.hpp"

void Polynomial::shiftRightFrom(size_t ind) {
        for (size_t i = terms.size() - 1; i > ind; i--) {
            terms[i] = terms[i-1];
        }
}
void Polynomial::shiftLeftFrom(size_t ind) {
  for (size_t i = ind; i < terms.size() - 1; i++) {
    terms[i] = terms[i + 1];
  }
}
void Polynomial::addTerm(const Term &t) {
  if (t.coefficient == Rational(0))
    return;
  for (size_t i = 0; i < terms.size(); i++) {
    if (t.exponent > terms[i].exponent) {
      terms.push_back(t);
      shiftRightFrom(i);
      terms[i] = t;
      return;
    } else if (t.exponent == terms[i].exponent) {
      terms[i].coefficient = terms[i].coefficient + t.coefficient;
      if (terms[i].coefficient == Rational()) {
        shiftLeftFrom(i);
        terms.pop_back();
      }
      return;
    }
  }
  terms.push_back(t);
}
Polynomial::Polynomial(const Array<Term> &arr) : terms(arr) {}
Polynomial::Polynomial(const Rational &coefficient, unsigned exponent) {
  addTerm(Term{coefficient, exponent});
}
Polynomial Polynomial::operator+(const Polynomial &other) const {
  Polynomial result(*this);
  for (const Term &term : other.terms) {
    result.addTerm(term);
  }
  return result;
}
Polynomial Polynomial::operator*(const Polynomial &other) const {
  Polynomial result;
  for (const Term &tLeft : terms) {
    for (const Term &tRight : other.terms) {
      result.addTerm({tLeft.coefficient * tRight.coefficient,
                      tLeft.exponent + tRight.exponent});
    }
  }
  return result;
}
Polynomial Polynomial::operator-() const {
  return Polynomial(terms.map<Term>(
      [](const Term &t) { return Term{-t.coefficient, t.exponent}; }));
}
Polynomial Polynomial::operator/(const Polynomial &other) const {
  if (other.degree() == -1)
    throw std::runtime_error("division by zero");
  Polynomial result;
  Polynomial remainder(*this);
  while (remainder.degree() >= other.degree()) {
    Term resultTerm =
        Term{remainder.terms[0].coefficient / other.terms[0].coefficient,
             (size_t)(remainder.degree() - other.degree())};
    result.addTerm(resultTerm);
    remainder =
        remainder - Polynomial(other.terms.map<Term>([&](const Term &term) {
          return Term{resultTerm.coefficient * term.coefficient,
                      resultTerm.exponent + term.exponent};
        }));
  }
  return result;
}
long long Polynomial::degree() const {
  if (terms.empty())
    return -1;
  return terms[0].exponent;
}

bool Polynomial::lessThan(const Polynomial &other) const {
  int deg1 = degree();
  int deg2 = other.degree();
  if (deg1 != deg2)
    return deg1 < deg2;

  size_t i = 0;
  size_t j = 0;
  for (int exp = deg1; exp >= 0; --exp) {

    Rational c1(0);
    if (i < terms.size() && terms[i].exponent == exp) {
      c1 = terms[i].coefficient;
      ++i;
    }

    Rational c2(0);
    if (j < other.terms.size() && other.terms[j].exponent == exp) {
      c2 = other.terms[j].coefficient;
      ++j;
    }
    if (c1 != c2)
      return c1 < c2;
  }
  return false;
}
void Polynomial::serialize(std::ostream &out) const {
  if (terms.size() == 0) {
    out << "0";
    return;
  }
  bool first = true;
  for (const Term &t : terms) {
    Rational c = t.coefficient;
    if (c == Rational(0, 1))
      continue;

    if (!first && c > Rational(0, 1))
      out << "+";
    if (c < Rational(0, 1))
      out << "-";

    Rational absC = c < Rational(0, 1) ? -c : c;
    if (t.exponent == 0) {
      out << absC;
    } else {
      if (absC != Rational(1, 1)) {
        out << absC << "*";
      }
      out << "x";
      if (t.exponent > 1)
        out << "^" << t.exponent;
    }
    first = false;
  }
}
