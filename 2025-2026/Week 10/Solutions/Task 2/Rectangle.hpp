#pragma once
#include "Shape.hpp"

class Rectangle : public Shape {
    Point bottomLeft;
    Point topRight;
public:
  Rectangle() = default;
  Rectangle(const Point &bottomLeft, const Point &topRight);
  double Area() const override;

  double Perimeter() const override;

  bool isIn(Point p) const override;

  void serialize(std::ostream &out) const override;
};