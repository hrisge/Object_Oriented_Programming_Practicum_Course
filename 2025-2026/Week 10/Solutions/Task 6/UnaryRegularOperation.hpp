#pragma once
#include "RegularExpression.hpp"

class UnaryRegularOperation : public RegularExpression{
protected:
    RegularExpression* expr;
    void free();
    void copy(const UnaryRegularOperation &other);

  public:
    UnaryRegularOperation(const RegularExpression &expr);
    UnaryRegularOperation(const UnaryRegularOperation &other);
    UnaryRegularOperation &operator=(const UnaryRegularOperation &other);
    ~UnaryRegularOperation() override;
};