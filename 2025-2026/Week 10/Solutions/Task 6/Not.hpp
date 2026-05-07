#pragma once

#include "RegularExpression.hpp"
#include "UnaryRegularOperation.hpp"

class Not : public UnaryRegularOperation{

public:
    Not(const RegularExpression& expr) : UnaryRegularOperation(expr) {}
    bool eval(const std::string &string) const override {
      return !expr->eval(string);
    }

    bool evalPrefix(const std::string &string, size_t n) const override {
      return !expr->evalPrefix(string, n);
    }

    void serialize(std::ostream &out) const override {
      out << "~(" << *expr << ")";
    }

    void deserialize(std::istream& in) override {
        char c;
        in >> c;
        if(c!='~'){
            throw std::runtime_error("Invalid serialization for Not");
        }
        in >> c;
        if (c != '(') {
            throw std::runtime_error("Invalid serialization for Not");
        }
        expr->deserialize(in);
        in >> c;
        if(c != ')'){
            throw std::runtime_error("Invalid serialization for Not");
        }

    }

    RegularExpression* clone() const override {
      return new Not(*this);
    }

};