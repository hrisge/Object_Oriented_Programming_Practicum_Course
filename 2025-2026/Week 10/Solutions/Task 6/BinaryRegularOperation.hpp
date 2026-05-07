#pragma once
#include "RegularExpression.hpp"

class BinaryRegularOperation : public RegularExpression{
protected:
    RegularExpression* expr1;
    RegularExpression* expr2;
    void free() {
        delete expr1;
        delete expr2;
    }
    void copy(const BinaryRegularOperation& other) {
        expr1 = other.expr1->clone();
        expr2 = other.expr2->clone();
    }

public:
    BinaryRegularOperation(const RegularExpression& expr1, const RegularExpression& expr2) : expr1(expr1.clone()), expr2(expr2.clone()) {}
    BinaryRegularOperation(const BinaryRegularOperation& other) {
        copy(other);
    }
    BinaryRegularOperation& operator=(const BinaryRegularOperation& other) {
        if(this == &other) return *this;
        free();
        copy(other);
        return *this;
    }
    ~BinaryRegularOperation() override {
        free();
    }
};