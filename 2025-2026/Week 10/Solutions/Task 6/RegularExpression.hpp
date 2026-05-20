#pragma once
#include "Deserializable.hpp"
#include "Serializable.hpp"
#include <string>


class RegularExpression : public Serializable, public Deserializable {
public:
    virtual bool eval(const std::string& string) const = 0;
    virtual bool evalPrefix(const std::string& string, size_t n) const = 0;
    virtual RegularExpression* clone() const = 0;
    virtual ~RegularExpression() = default;
};