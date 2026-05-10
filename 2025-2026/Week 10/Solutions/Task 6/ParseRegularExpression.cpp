#include "ParseRegularExpression.hpp"

#include "Difference.hpp"
#include "Star.hpp"
#include "Union.hpp"
#include "Var.hpp"
#include "Empty.hpp"
#include "Not.hpp"
#include "Intersect.hpp"
#include "Any.hpp"
#include "Concat.hpp"
#include <stdexcept>


RegularExpression *parseRegularExpression(std::istream &in) {
  if (!in) throw std::runtime_error("invalid stream");
  char c;
  in >> c;
  if (c == '?') return new Any();
  else if (c == '@') return new Empty();
  else if (c == '~') {
    in >> c;
    if (c != '(') throw std::runtime_error("invalid regex");

    RegularExpression *regex = parseRegularExpression(in);
    in >> c;

    if (c != ')') throw std::runtime_error("invalid regex");

    return new Not(*regex);
  } 
  else if (c == '(') {
    RegularExpression *first = parseRegularExpression(in);
    in >> c;
    
    if (c == ')') {
      in >> c;
      if (c == '*') return new Star(*first);
      else throw std::runtime_error("invalid regEx");
    } 
    else {
        RegularExpression *second = parseRegularExpression(in);
        char op = c;
        in >> c;
        if (c != ')') throw std::runtime_error("invalid regex");
        if (op == '&') return new Intersect(*first, *second);
        else if (op == '|') return new Union(*first, *second);
        else if (op == '.') return new Concat(*first, *second);
        else if (op == '\\') return new Difference(*first, *second);
        else throw std::runtime_error("invalid regex");
    }
  } 
  else {
    std::string str;
    std::string ch;
    ch.push_back(c);
    in >> str;
    str = ch.append(str);
    return new Var(str.c_str());
  }
}