#include "Expr.hpp"

#include "Add.hpp"
#include "Const.hpp"
#include "Subtract.hpp"
#include "Multiply.hpp"
#include "Divide.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

bool isDigit(char c) {
    return '0' <= c && c <= '9';
}

Expr* fromStringstream(std::stringstream& stream){
    if(stream.fail()) return nullptr;
    while(stream && stream.peek() == ' ') stream.get();
    if(isDigit(stream.peek()) || stream.peek() == '-'){
        int number;
        stream >> number;
        return new Const(number);
    }
    else if(stream.peek() == '('){
        stream.get();
        Expr* left = fromStringstream(stream);
        char op;
        stream >> op;
        Expr* right = fromStringstream(stream);

        Expr* result;
        switch (op) {
            case '+': result = new Add(*left, *right); break;
            case '-': result = new Subtract(*left, *right); break;
            case '*': result = new Multiply(*left, *right); break;
            case '/': result = new Divide(*left, *right); break;
            default: throw std::runtime_error("invalid operator");
        }
        char closingBracket;
        stream >> closingBracket;
        if(closingBracket != ')') throw std::runtime_error("invalid expression");
        delete left;
        delete right;

        return result;
    }
    else throw std::runtime_error("invalid expression");
}

Expr* Expr::fromString(const std::string &string) {
    std::stringstream stream(string);
    return fromStringstream(stream);
}