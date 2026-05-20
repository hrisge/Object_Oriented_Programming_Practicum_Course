
#include "Circle.hpp"

double Circle::Area() const {
        return radius * radius * 3.14;
}

Circle::Circle() 
: radius(1), center(0, 0) {}

Circle::Circle(const Point &center, double radius)
      : center(center), radius(radius) {}

double Circle::Perimeter() const{
        return 2 * radius * 3.14;
}

bool Circle::isIn(Point p) const{
        return p.distanceTo(center) <= radius;
}

void Circle::serialize(std::ostream& out) const {
        out << center << " " << radius;
}