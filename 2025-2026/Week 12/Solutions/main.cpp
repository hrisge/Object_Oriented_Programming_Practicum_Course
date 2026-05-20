#include "Expr.hpp"
#include <iostream>


int main() {
    std::string expr = "(((2 + ((1 - 5) * 4)) / -7) / (4 * (1 / (10 - 2))))";
    Expr* ex = Expr::fromString(expr);
    std::cout << ex->eval() << std::endl;
    delete ex;
}
