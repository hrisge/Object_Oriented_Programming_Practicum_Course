#include "Union.hpp"
#include "ParseRegularExpression.hpp"

RegularExpression *Union::clone() const { return new Union(*expr1, *expr2); }
Union::Union(const RegularExpression &expr1, const RegularExpression &expr2)
    : BinaryRegularOperation(expr1, expr2) {}
bool Union::eval(const std::string &string) const {
  return expr1->eval(string) || expr2->eval(string);
}
bool Union::evalPrefix(const std::string &string, size_t n) const {
  return expr1->evalPrefix(string, n) || expr2->evalPrefix(string, n);
}
void Union::serialize(std::ostream &out) const {
  out << "(" << *expr1 << " | " << *expr2 << ")";
}
void Union::deserialize(std::istream &in) {
  free();
  char c;
  in >> c;
  if (c != '(') {
    throw std::runtime_error("Invalid serialization for Union");
  }
  expr1 = parseRegularExpression(in);
  in >> c;
  if (c != '|') {
    throw std::runtime_error("Invalid serialization for Union");
  }
  expr2 = parseRegularExpression(in);
  in >> c;
  if (c != ')') {
    throw std::runtime_error("Invalid serialization for Union");
  }
}
