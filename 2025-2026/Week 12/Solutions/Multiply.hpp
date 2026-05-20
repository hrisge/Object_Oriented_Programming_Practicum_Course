#pragma once

#include "BinOp.hpp"
class Multiply : public BinOp {

public:
  Multiply(const Expr& left, const Expr& right);
  double eval() const override;
  Multiply *clone() const override;
};