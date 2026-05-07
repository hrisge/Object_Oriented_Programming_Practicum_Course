#include "Serializable.hpp"

std::ostream& operator<<(std::ostream& out, const Serializable& serializable){
    serializable.serialize(out);
    return out;
}