#include "Rectangle.hpp"

Rectangle::Rectangle(const Point &bottomLeft, const Point &topRight)
    : bottomLeft(bottomLeft), topRight(topRight) {}


double Rectangle::Area() const {
    return ((topRight.x - bottomLeft.x) + (topRight.y - bottomLeft.y)) * 2;
}
double Rectangle::Perimeter() const {
  return (topRight.x - bottomLeft.x) * (topRight.y - bottomLeft.y);
}
bool Rectangle::isIn(Point p) const {
  return p.x >= bottomLeft.x && p.x <= topRight.x && p.y <= topRight.y &&
         p.y >= bottomLeft.y;
}
void Rectangle::serialize(std::ostream &out) const {
  out << bottomLeft << " " << topRight;
}
