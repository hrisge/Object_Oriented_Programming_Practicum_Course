#pragma once
#include "RegularExpression.hpp"

class UnaryRegularOperation : public RegularExpression{
protected:
    RegularExpression* expr;
    void free() {
        delete expr;
    }
    void copy(const UnaryRegularOperation& other) {
        expr = other.expr->clone();
    }

public:
    UnaryRegularOperation(const RegularExpression& expr) : expr(expr.clone()) {}
    UnaryRegularOperation(const UnaryRegularOperation& other) {
        copy(other);
    }
    UnaryRegularOperation& operator=(const UnaryRegularOperation& other) {
        if(this == &other) return *this;
        free();
        copy(other);
        return *this;
    }
    ~UnaryRegularOperation() override {
        free();
    }
};