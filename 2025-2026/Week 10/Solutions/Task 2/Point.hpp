#pragma once
#include "Deserializable.hpp"
#include "Ordered.hpp"
#include "Serializable.hpp"
#include <cmath>
#include "Ordered.hpp"

struct Point : public Serializable, public Deserializable, public Ordered<Point> {
    double x;
    double y;
    Point() = default;
    Point(double x, double y);

    void serialize(std::ostream& out) const override ;
    void deserialize(std::istream &in) override;
    double distanceTo(const Point &other) const;

    bool lessThan(const Point &other) const override;
};