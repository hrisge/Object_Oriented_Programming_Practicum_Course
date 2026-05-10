#include "Var.hpp"

Var::Var(const char *str) : str(str) {}
bool Var::eval(const std::string &string) const { return this->str == string; }
bool Var::evalPrefix(const std::string &string, size_t n) const {
  if (n != str.length())
    return false;
  return string.substr(0, n) == str;
}
void Var::serialize(std::ostream &out) const { out << str; }
void Var::deserialize(std::istream &in) { in >> str; }
RegularExpression *Var::clone() const { return new Var(str.c_str()); }
