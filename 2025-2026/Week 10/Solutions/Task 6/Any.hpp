#pragma once

#include "RegularExpression.hpp"
class Any : public RegularExpression {

public:
  RegularExpression *clone() const override;

  bool eval(const std::string &string) const override;

  bool evalPrefix(const std::string &string, size_t n) const override;

  void serialize(std::ostream &out) const override;

  void deserialize(std::istream &in) override;
};