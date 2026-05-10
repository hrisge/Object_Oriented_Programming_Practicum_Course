#include "BinaryRegularOperation.hpp"

void BinaryRegularOperation::free() {
        delete expr1;
        delete expr2;
}
void BinaryRegularOperation::copy(const BinaryRegularOperation &other) {
  expr1 = other.expr1->clone();
  expr2 = other.expr2->clone();
}
BinaryRegularOperation::BinaryRegularOperation(const RegularExpression &expr1,
                                               const RegularExpression &expr2)
    : expr1(expr1.clone()), expr2(expr2.clone()) {}
BinaryRegularOperation::BinaryRegularOperation(
    const BinaryRegularOperation &other) {
  copy(other);
}
BinaryRegularOperation &
BinaryRegularOperation::operator=(const BinaryRegularOperation &other) {
  if (this == &other)
    return *this;
  free();
  copy(other);
  return *this;
}
BinaryRegularOperation::~BinaryRegularOperation() { free(); }
