#include "UnaryRegularOperation.hpp"

void UnaryRegularOperation::free() { delete expr; }
void UnaryRegularOperation::copy(const UnaryRegularOperation &other) {
  expr = other.expr->clone();
}
UnaryRegularOperation::UnaryRegularOperation(const RegularExpression &expr)
    : expr(expr.clone()) {}
UnaryRegularOperation::UnaryRegularOperation(
    const UnaryRegularOperation &other) {
  copy(other);
}
UnaryRegularOperation &
UnaryRegularOperation::operator=(const UnaryRegularOperation &other) {
  if (this == &other)
    return *this;
  free();
  copy(other);
  return *this;
}
UnaryRegularOperation::~UnaryRegularOperation() { free(); }
