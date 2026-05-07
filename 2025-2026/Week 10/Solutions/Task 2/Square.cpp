#include "Square.hpp"

Square::Square() : Rectangle() {}
Square::Square(const Point &bottomLeft, double size)
    : Rectangle(bottomLeft, Point(bottomLeft.x + size, bottomLeft.y + size)) {}
