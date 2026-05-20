#include "Subtract.hpp"

Subtract::Subtract(const Expr &left, const Expr &right) : BinOp(left, right) {}
double Subtract::eval() const { return left->eval() - right->eval(); }
Subtract *Subtract::clone() const { return new Subtract(*this); }
