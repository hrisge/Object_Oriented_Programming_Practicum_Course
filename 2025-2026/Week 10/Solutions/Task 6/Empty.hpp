#pragma once

#include "RegularExpression.hpp"
#include <cstddef>
#include <stdexcept>
class Empty : public RegularExpression {

public:
  bool eval(const std::string& string) const override {
    return string.empty();
  }

  bool evalPrefix(const std::string& string, size_t n) const override {
    return n == 0;
  }

  void serialize(std::ostream &out) const override {
     out << "@";
  }

  void deserialize(std::istream& in) override {
    char c;
    in >> c;
    if(c != '@') throw std::runtime_error("Invalid serialization for Empty");
  }

  RegularExpression* clone() const override {
    return new Empty(*this);
  }
  
};