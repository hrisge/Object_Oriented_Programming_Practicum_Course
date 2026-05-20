#include "Multiply.hpp"

Multiply::Multiply(const Expr &left, const Expr &right) : BinOp(left, right) {}
double Multiply::eval() const { return left->eval() * right->eval(); }
Multiply *Multiply::clone() const { return new Multiply(*this); }
