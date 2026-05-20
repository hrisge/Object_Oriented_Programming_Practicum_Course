#pragma once
#include <iostream>

class Serializable{
public:
    virtual void serialize(std::ostream& out) const = 0;
};

std::ostream& operator<<(std::ostream& out, const Serializable& serializable);