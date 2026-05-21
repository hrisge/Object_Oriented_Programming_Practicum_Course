#pragma once

#include "Expr.hpp"
class BinOp : public Expr {
protected:
    Expr* left;
    Expr* right;
public:
    BinOp(const Expr& left, const Expr& right);
    BinOp(const BinOp &other);
    BinOp &operator=(const BinOp &other);
    ~BinOp() override;
};