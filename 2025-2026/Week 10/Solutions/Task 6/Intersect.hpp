#pragma once
#include "BinaryRegularOperation.hpp"
#include "RegularExpression.hpp"

class Intersect : public BinaryRegularOperation{

public:
  Intersect(RegularExpression& expr1, RegularExpression& expr2) : BinaryRegularOperation(expr1, expr2) {}
  bool eval(const std::string &string) const override {
    return expr1->eval(string) && expr2->eval(string);
  }

  bool evalPrefix(const std::string &string, size_t n) const override {
    return expr1->evalPrefix(string, n) && expr2->evalPrefix(string, n);
  }

  void serialize(std::ostream &out) const override {
    out << "(" << expr1 << " & " << expr2 << ")";
  }

  void deserialize(std::istream& in) override{
        char c;
        in >> c;
        if (c != '(') {
            throw std::runtime_error("Invalid serialization for Intersect");
        }
        expr1->deserialize(in);
        in >> c;
        if(c != '&'){
            throw std::runtime_error("Invalid serialization for Intersect");
        }
        expr2->deserialize(in);
        in >> c;
        if(c != ')'){
            throw std::runtime_error("Invalid serialization for Intersect");
        }
  }

  RegularExpression* clone() const override {
      return new Intersect(*this);
  }
};