#pragma once

#include "BinOp.hpp"
class Divide : public BinOp{

public:
  Divide(const Expr& left, const Expr& right);
  double eval() const override;
  Divide *clone() const override;
};