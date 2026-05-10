#pragma once
#include "RegularExpression.hpp"
#include "UnaryRegularOperation.hpp"

class Star : public UnaryRegularOperation {
public:
    Star(const RegularExpression& expr);
    bool eval(const std::string &string) const override;

    bool evalPrefix(const std::string &string, size_t n) const override;

    void serialize(std::ostream &out) const override;

    void deserialize(std::istream &in) override;

    RegularExpression *clone() const override;
};