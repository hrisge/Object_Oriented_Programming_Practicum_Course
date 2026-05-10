
#include "Concat.hpp"
#include "ParseRegularExpression.hpp"

Concat::Concat(const RegularExpression &expr1, const RegularExpression &expr2)
    : BinaryRegularOperation(expr1, expr2) {}
bool Concat::eval(const std::string &string) const {
  for (size_t i = 0; i < string.size(); i++) {
    if (expr1->evalPrefix(string, i) && expr2->eval(string.substr(i)))
      return true;
  }
  return false;
}

bool Concat::evalPrefix(const std::string &string, size_t n) const {
        return eval(string.substr(0, n));
}
void Concat::serialize(std::ostream &out) const {
  out << "(" << *expr1 << " . " << *expr2 << ")";
}
void Concat::deserialize(std::istream &in) {
  free();
  char c;
  in >> c;
  if (c != '(') {
    throw std::runtime_error("Invalid serialization for Concat");
  }
  expr1 = parseRegularExpression(in);
  in >> c;
  if (c != '.') {
    throw std::runtime_error("Invalid serialization for Concat");
  }
  expr2 = parseRegularExpression(in);
  in >> c;
  if (c != ')') {
    throw std::runtime_error("Invalid serialization for Concat");
  }
}
RegularExpression *Concat::clone() const { return new Concat(*this); }
