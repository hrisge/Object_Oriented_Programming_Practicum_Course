#pragma once
#include "RegularExpression.hpp"
#include "BinaryRegularOperation.hpp"

class Concat : public BinaryRegularOperation{

public:
  Concat(const RegularExpression &expr1, const RegularExpression &expr2);
  bool eval(const std::string &string) const override;

  bool evalPrefix(const std::string &string, size_t n) const override;

  void serialize(std::ostream &out) const override;

  void deserialize(std::istream &in) override;

  RegularExpression *clone() const override;
};