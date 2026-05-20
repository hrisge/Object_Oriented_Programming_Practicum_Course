#include "Add.hpp"
#include "BinOp.hpp"
#include "Expr.hpp"

Add::Add(const Expr &left, const Expr &right) : BinOp(left, right) {}
double Add::eval() const { return left->eval() + right->eval(); }
Add *Add::clone() const { return new Add(*this); }
