#include "Not.hpp"

Not::Not(const RegularExpression &expr) : UnaryRegularOperation(expr) {}
bool Not::eval(const std::string &string) const { return !expr->eval(string); }
bool Not::evalPrefix(const std::string &string, size_t n) const {
  return !expr->evalPrefix(string, n);
}
void Not::serialize(std::ostream &out) const { out << "~(" << *expr << ")"; }
void Not::deserialize(std::istream &in) {
  free();
  char c;
  in >> c;
  if (c != '~') {
    throw std::runtime_error("Invalid serialization for Not");
  }
  in >> c;
  if (c != '(') {
    throw std::runtime_error("Invalid serialization for Not");
  }
  expr = parseRegularExpression(in);
  in >> c;
  if (c != ')') {
    throw std::runtime_error("Invalid serialization for Not");
  }
}
RegularExpression *Not::clone() const { return new Not(*this); }
