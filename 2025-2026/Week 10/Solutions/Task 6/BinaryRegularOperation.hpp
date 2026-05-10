#pragma once
#include "RegularExpression.hpp"

class BinaryRegularOperation : public RegularExpression{
protected:
    RegularExpression* expr1;
    RegularExpression* expr2;
    void free();
    void copy(const BinaryRegularOperation &other);

  public:
    BinaryRegularOperation(const RegularExpression &expr1,
                           const RegularExpression &expr2);
    BinaryRegularOperation(const BinaryRegularOperation &other);
    BinaryRegularOperation &operator=(const BinaryRegularOperation &other);
    ~BinaryRegularOperation() override;
};