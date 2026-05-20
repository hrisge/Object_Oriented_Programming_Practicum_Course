#include "Divide.hpp"

Divide::Divide(const Expr &left, const Expr &right) : BinOp(left, right) {}
double Divide::eval() const { return left->eval() / right->eval(); }
Divide *Divide::clone() const { return new Divide(*this); }
