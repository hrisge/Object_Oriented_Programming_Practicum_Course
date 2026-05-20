#pragma once
#include <iostream>

class Deserializable {
public:
    virtual void deserialize(std::istream& in) = 0;
};

std::istream& operator>>(std::istream& in, Deserializable& deserializable);