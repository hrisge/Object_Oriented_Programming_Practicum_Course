#include "BinOp.hpp"

BinOp::BinOp(const Expr &left, const Expr &right)
    : left(left.clone()), right(right.clone()) {}
BinOp::BinOp(const BinOp &other)
    : left(other.left->clone()), right(other.right->clone()) {}
BinOp &BinOp::operator=(const BinOp &other) {
  if (this == &other)
    return *this;

  left = other.left->clone();
  right = other.right->clone();
  return *this;
}
BinOp::~BinOp() {
  delete left;
  delete right;
}
