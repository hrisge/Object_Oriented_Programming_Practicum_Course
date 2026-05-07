#pragma once
#include "Rectangle.hpp"

class Square : public Rectangle {
public:
    Square();
    Square(const Point &bottomLeft, double size);
};