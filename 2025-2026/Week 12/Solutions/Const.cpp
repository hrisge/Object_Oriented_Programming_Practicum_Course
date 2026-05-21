#include "Const.hpp"

Const::Const(int number) : number(number) {}
double Const::eval() const { return number; }
Const *Const::clone() const { return new Const(*this); }
