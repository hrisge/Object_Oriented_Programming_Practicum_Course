#pragma once

#include "RegularExpression.hpp"
class Var : public RegularExpression{
    std::string str;
public:
  Var(const std::string& str) : str(str) {}
  bool eval(const std::string& string) const override {
    return this->str == string;
  }

  bool evalPrefix(const std::string& string, size_t n) const override {
    if(n != str.length()) return false;
    return string.substr(0, n) == str;
  }

  void serialize(std::ostream &out) const override {
    out << str;
  }

  void deserialize(std::istream& in) override {
    in >> str;
  }
};