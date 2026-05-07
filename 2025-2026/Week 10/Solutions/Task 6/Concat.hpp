#pragma once

#include "RegularExpression.hpp"
#include "BinaryRegularOperation.hpp"

class Concat : public BinaryRegularOperation{

public:

    Concat(const RegularExpression& expr1, const RegularExpression& expr2) : BinaryRegularOperation(expr1, expr2) {}
    bool eval(const std::string &string) const override {
        for(size_t i = 0; i < string.size(); i++){
            if(expr1->evalPrefix(string, i) && expr2->eval(string.substr(i))) return true;
        }
        return false;
    }

    bool evalPrefix(const std::string &string, size_t n) const override {
        return eval(string.substr(0, n));
    }

    void serialize(std::ostream &out) const override {
        out << "(" << *expr1 << " . " << *expr2 << ")";
    }

    void deserialize(std::istream &in) override {
        char c;
        in >> c;
        if (c != '(') {
            throw std::runtime_error("Invalid serialization for Concat");
        }
        expr1->deserialize(in);
        in >> c;
        if(c != '.'){
            throw std::runtime_error("Invalid serialization for Concat");
        }
        expr2->deserialize(in);
        in >> c;
        if(c != ')'){
            throw std::runtime_error("Invalid serialization for Concat");
        }
    }

    RegularExpression* clone() const override {
        return new Concat(*this);
    }

};