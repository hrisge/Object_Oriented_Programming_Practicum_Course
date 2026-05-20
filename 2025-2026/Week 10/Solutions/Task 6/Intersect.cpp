#include "Intersect.hpp"
#include "ParseRegularExpression.hpp"

Intersect::Intersect(const RegularExpression &expr1,
                     const RegularExpression &expr2)
    : BinaryRegularOperation(expr1, expr2) {}
bool Intersect::eval(const std::string &string) const {
  return expr1->eval(string) && expr2->eval(string);
}
bool Intersect::evalPrefix(const std::string &string, size_t n) const {
  return expr1->evalPrefix(string, n) && expr2->evalPrefix(string, n);
}
void Intersect::serialize(std::ostream &out) const {
  out << "(" << expr1 << " & " << expr2 << ")";
}
void Intersect::deserialize(std::istream &in) {
  free();
  char c;
  in >> c;
  if (c != '(') {
    throw std::runtime_error("Invalid serialization for Intersect");
  }
  expr1 = parseRegularExpression(in);
  in >> c;
  if (c != '&') {
    throw std::runtime_error("Invalid serialization for Intersect");
  }
  expr2 = parseRegularExpression(in);
  in >> c;
  if (c != ')') {
    throw std::runtime_error("Invalid serialization for Intersect");
  }
}
RegularExpression *Intersect::clone() const { return new Intersect(*this); }
