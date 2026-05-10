#include "Empty.hpp"

bool Empty::eval(const std::string &string) const { return string.empty(); }
bool Empty::evalPrefix(const std::string &string, size_t n) const {
  return n == 0;
}
void Empty::serialize(std::ostream &out) const { out << "@"; }
void Empty::deserialize(std::istream &in) {
  char c;
  in >> c;
  if (c != '@')
    throw std::runtime_error("Invalid serialization for Empty");
}
RegularExpression *Empty::clone() const { return new Empty(*this); }
