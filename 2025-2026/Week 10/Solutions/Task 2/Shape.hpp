#pragma once
#include "Point.hpp"
#include "Serializable.hpp"

class Shape : public Serializable {
public:
    virtual double Area() const = 0;
    virtual double Perimeter() const = 0;
    virtual bool isIn(Point p) const = 0;
};