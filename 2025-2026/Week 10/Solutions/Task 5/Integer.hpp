#pragma once
#include "Integral.hpp"

class Integer : public Integral<Integer>{
    int number;
public:
  Integer();
  Integer(int number);
  Integer operator+(const Integer &other) const override;
  Integer operator*(const Integer &other) const override;
  Integer operator-() const override;
  using Integral<Integer>::operator-;
  Integer operator/(const Integer &other) const override;
  bool lessThan(const Integer &other) const override;
  void serialize(std::ostream &out) const override;
};