#pragma once

#include "Expr.hpp"
class Const : public Expr {
  int number;
public:
  Const(int number);
  double eval() const override;
  Const *clone() const override;
};