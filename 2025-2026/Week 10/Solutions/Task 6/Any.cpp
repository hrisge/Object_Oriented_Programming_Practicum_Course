#include "Any.hpp"

RegularExpression *Any::clone() const { return new Any(*this); }
bool Any::eval(const std::string &string) const { return string.size() == 1; }
bool Any::evalPrefix(const std::string &string, size_t n) const {
  return n == 1;
}
void Any::serialize(std::ostream &out) const { out << "?"; }
void Any::deserialize(std::istream &in) {
  char c;
  in >> c;
  if (c != '?') {
    throw std::runtime_error("Invalid serialization for Any");
  }
}
