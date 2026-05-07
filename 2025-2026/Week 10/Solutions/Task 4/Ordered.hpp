#pragma once
#include "Equal.hpp"

template <class T>
class Ordered : public Equal<T> {
    Ordered() = default;
    friend T;
    friend Integral<T>;
    public:
    virtual bool lessThan(const T&) const = 0;
    bool equals(const T &other) const final;

    bool operator<(const Ordered<T> &other) const;
    bool operator>(const Ordered<T> &other) const;
    bool operator<=(const Ordered<T> &other) const;
    bool operator>=(const Ordered<T> &other) const;
};

template <class T> bool Ordered<T>::equals(const T &other) const {
  const T *self = static_cast<const T *>(this);
  return !(self->lessThan(other) || other.lessThan(*self));
}

template <class T>
bool Ordered<T>::operator<(const Ordered<T> &other) const {
  const T *leftT = static_cast<const T *>(this);
  const T *rightT = static_cast<const T *>(&other);
  return leftT->lessThan(*rightT);
}

template <class T>
bool Ordered<T>::operator>(const Ordered<T> &other) const {
  return other < *this;
}

template <class T>
bool Ordered<T>::operator<=(const Ordered<T> &other) const {
  return !(other < *this);
}

template <class T>
bool Ordered<T>::operator>=(const Ordered<T> &other) const {
  return !(*this < other);
}
