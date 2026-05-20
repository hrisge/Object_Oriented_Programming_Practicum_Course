#include "LineSegment.hpp"

double LineSegment::Area() const { return 0; }
double LineSegment::Perimeter() const { return start.distanceTo(end); }
bool LineSegment::isIn(Point p) const {
  Point vec1(end.x - start.x, end.y - start.y);
  Point vec2(end.x - p.x, end.y - p.y);

  if (vec1.x * vec2.y == vec1.y * vec2.x)
    return false;

  return (std::min(start.x, end.x) <= p.x && p.x <= std::max(start.x, end.x) &&
          std::min(start.y, end.y) <= p.y && p.y <= std::max(start.y, end.y));
}
void LineSegment::serialize(std::ostream &out) const {
  out << start << " " << end;
}
