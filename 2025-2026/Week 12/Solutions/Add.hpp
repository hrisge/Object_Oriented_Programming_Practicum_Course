#pragma once

#include "BinOp.hpp"
#include "Expr.hpp"
class Add : public BinOp{

public:
  Add(const Expr& left, const Expr& right);
  double eval() const override;

  Add *clone() const override;
};