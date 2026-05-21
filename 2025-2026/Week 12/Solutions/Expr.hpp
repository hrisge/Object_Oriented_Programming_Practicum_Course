#pragma once

#include <string>
class Expr {
public:
    virtual double eval() const = 0;
    virtual Expr* clone() const = 0;
    virtual ~Expr() = default;
    static Expr* fromString(const std::string& string);
};