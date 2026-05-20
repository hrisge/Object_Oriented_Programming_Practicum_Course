#include "Star.hpp"
#include "ParseRegularExpression.hpp"

Star::Star(const RegularExpression &expr) : UnaryRegularOperation(expr) {}
bool Star::eval(const std::string &string) const {
  if (string.empty())
    return true;
  for (size_t i = 0; i <= string.size(); i++) {
    if (expr->evalPrefix(string, i) && eval(string.substr(i)))
      return true;
  }
  return false;
}
bool Star::evalPrefix(const std::string &string, size_t n) const {
  return eval(string.substr(0, n));
}
void Star::serialize(std::ostream &out) const { out << "(" << *expr << ")*"; }
void Star::deserialize(std::istream &in) {
  free();
  char c;
  in >> c;

  if (c != '(') {
    throw std::runtime_error("Invalid serialization for Star");
  }
  expr = parseRegularExpression(in);
  in >> c;
  if (c != ')') {
    throw std::runtime_error("Invalid serialization for Star");
  }
  in >> c;
  if (c != '*') {
    throw std::runtime_error("Invalid serialization for Star");
  }
}
RegularExpression *Star::clone() const { return new Star(*this); }
