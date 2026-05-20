#include "Difference.hpp"
#include "ParseRegularExpression.hpp"

Difference::Difference(const RegularExpression &expr1,
                       const RegularExpression &expr2)
    : BinaryRegularOperation(expr1, expr2) {}
    
bool Difference::eval(const std::string &string) const {
  return expr1->eval(string) && !expr2->eval(string);
}
bool Difference::evalPrefix(const std::string &string, size_t n) const {
  return expr1->evalPrefix(string, n) && !expr2->evalPrefix(string, n);
}
void Difference::serialize(std::ostream &out) const {
  out << "(" << expr1 << " \\ " << expr2 << ")";
}
void Difference::deserialize(std::istream &in) {
  free();
  char c;
  in >> c;
  if (c != '(') {
    throw std::runtime_error("Invalid serialization for Concat");
  }
  expr1 = parseRegularExpression(in);
  in >> c;
  if (c != '\\') {
    throw std::runtime_error("Invalid serialization for Concat");
  }
  expr2 = parseRegularExpression(in);
  in >> c;
  if (c != ')') {
    throw std::runtime_error("Invalid serialization for Concat");
  }
}
RegularExpression *Difference::clone() const { return new Difference(*this); }
