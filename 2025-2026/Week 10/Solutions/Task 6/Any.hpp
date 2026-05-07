#pragma once

#include "RegularExpression.hpp"
class Any : public RegularExpression {

public:
  RegularExpression *clone() const override {
    return new Any(*this);
  }

  bool eval(const std::string &string) const override {
    return string.size() == 1;
  }

  bool evalPrefix(const std::string &string, size_t n) const override {
    return n == 1;
  }

  void serialize(std::ostream &out) const override {
    out << "?";
  }

  void deserialize(std::istream &in) override {
        char c;
        in >> c;
        if (c != '?') {
            throw std::runtime_error("Invalid serialization for Any");
        }
  }

  
};