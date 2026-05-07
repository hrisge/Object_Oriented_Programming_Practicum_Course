#pragma once

template <class T>
class Ordered;
template <class T>
class Integral;

template <class T>
class Equal {
    Equal() = default;
    friend Integral<T>;
    friend Ordered<T>;
    friend T;
public:
    virtual bool equals(const T& other) const = 0;
};

template <class T>
bool operator==(const Equal<T>& left, const Equal<T>& right) {
    const T* leftT = static_cast<const T*>(&left);
    const T* rightT = static_cast<const T*>(&right);
    return leftT->equals(*rightT);
}

template <class T>
bool operator!=(const Equal<T>& left, const Equal<T>& right) {
   return !(left == right);
}