#pragma once

#include "Shape.hpp"

class LineSegment : public Shape {
    Point start;
    Point end;
public:
  double Area() const override;
  double Perimeter() const override;
  bool isIn(Point p) const override;
  void serialize(std::ostream &out) const override;
};