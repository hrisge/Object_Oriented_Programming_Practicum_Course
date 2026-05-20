#pragma once
#include "BinaryRegularOperation.hpp"
#include "RegularExpression.hpp"

class Difference : public BinaryRegularOperation {
    
public:

    Difference(const RegularExpression& expr1, const RegularExpression& expr2);
    bool eval(const std::string &string) const override;

    bool evalPrefix(const std::string &string, size_t n) const override;

    void serialize(std::ostream &out) const override;

    void deserialize(std::istream &in) override;

    RegularExpression *clone() const override;
};