#pragma once

#include "BinOp.hpp"
class Subtract : public BinOp {

public:
  Subtract(const Expr& left, const Expr& right);
  double eval() const override;
  Subtract *clone() const override;
};