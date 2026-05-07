#pragma once
#include "Any.hpp"
#include "RegularExpression.hpp"
#include "Var.hpp"
#include "Empty.hpp"
#include <stdexcept>

RegularExpression* parseRegularExpression(std::istream& in) {
    if(!in) throw "error";
    char c;
    in >> c;
    if(c == '?') return new Any();
    else if( c == '@') return new Empty();
    else if( c == '(') {
        RegularExpression* first = parseRegularExpression(in);
        in >> c;
        if(c == ')'){
            in >> c;
            if(c == '*'){
                return new Star(first);
            }
            else throw std::runtime_error("invalid regEx");
        }
        else if(c == '&'){
            
        }
    }

}