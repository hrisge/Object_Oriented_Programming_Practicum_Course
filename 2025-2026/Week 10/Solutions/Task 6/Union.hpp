#pragma once
#include "BinaryRegularOperation.hpp"
#include "RegularExpression.hpp"

class Union : public BinaryRegularOperation {

public:
  RegularExpression *clone() const override;

  Union(const RegularExpression &expr1, const RegularExpression &expr2);
  bool eval(const std::string &string) const override;

  bool evalPrefix(const std::string &string, size_t n) const override;

  void serialize(std::ostream &out) const override;

  void deserialize(std::istream &in) override;
};