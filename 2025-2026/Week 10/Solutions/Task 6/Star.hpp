#pragma once
#include "RegularExpression.hpp"
#include "UnaryRegularOperation.hpp"

class Star : public UnaryRegularOperation {
public:
    Star(const RegularExpression& expr) : UnaryRegularOperation(expr) {}
    bool eval(const std::string &string) const override {
      if(string.empty()) return true;
      for(size_t i = 0; i < string.size(); i++){
        if(expr->evalPrefix(string, i) && eval(string.substr(i))) return true;
      }
      return false;
    }

    bool evalPrefix(const std::string &string, size_t n) const override {
      return eval(string.substr(0,n));
    }

    void serialize(std::ostream &out) const override {
      out << "(" << *expr << ")*";
    }

    void deserialize(std::istream& in) override{
      char c;
        in >> c;
        
        if (c != '(') {
            throw std::runtime_error("Invalid serialization for Star");
        }
        expr->deserialize(in);
        in >> c;
        if(c != ')'){
            throw std::runtime_error("Invalid serialization for Star");
        }
        in >> c;
        if(c!='*'){
            throw std::runtime_error("Invalid serialization for Star");
        }
        
    }

    RegularExpression* clone() const override{
      return new Star(*this);
    }
};