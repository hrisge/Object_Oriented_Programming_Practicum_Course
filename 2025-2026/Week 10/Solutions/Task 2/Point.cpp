#include "Point.hpp"


Point::Point(double x, double y) : x(x), y(y) {}

void Point::serialize(std::ostream &out) const { out << x << " " << y; }

void Point::deserialize(std::istream &in) { in >> x >> y; }

double Point::distanceTo(const Point &other) const {
  return sqrt(pow((x - other.x), 2) * pow((y - other.y), 2));
}

bool Point::lessThan(const Point &other) const {
  return x < other.x || x == other.x && y < other.y;
}
