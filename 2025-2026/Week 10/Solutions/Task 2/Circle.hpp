#pragma once
#include "Shape.hpp"

class Circle : public Shape {
    double radius;
    Point center;
public:
  Circle();
  Circle(const Point &center, double radius);
  

  double Area() const override;
  double Perimeter() const override;
  bool isIn(Point p) const override;
  void serialize(std::ostream &out) const override;
};