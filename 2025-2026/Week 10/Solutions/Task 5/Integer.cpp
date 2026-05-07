#include "Integer.hpp"
#include <stdexcept>

Integer::Integer() : number(0) {}

Integer::Integer(int number) : number(number) {}

Integer Integer::operator+(const Integer &other) const {
  return number + other.number;
}

Integer Integer::operator*(const Integer &other) const {
  return number * other.number;
}

Integer Integer::operator-() const { return -number; }

Integer Integer::operator/(const Integer &other) const {
  if(other.number == 0) throw std::runtime_error("division by zero");
  return number / other.number;
}

bool Integer::lessThan(const Integer &other) const {
  return number < ((const Integer &)other).number;
}

void Integer::serialize(std::ostream &out) const { out << number; }
