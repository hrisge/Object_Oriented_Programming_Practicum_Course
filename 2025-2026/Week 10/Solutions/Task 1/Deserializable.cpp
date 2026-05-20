#include "Deserializable.hpp"

std::istream& operator>>(std::istream& in, Deserializable& deserializable){
    deserializable.deserialize(in);
    return in;
}