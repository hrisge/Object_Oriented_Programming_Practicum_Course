#pragma once
#include "Ordered.hpp"
#include "Serializable.hpp"

template <class T>
class Integral : public Ordered<T>, public Serializable {
private:

    Integral() = default;
    friend T;

public:
    
    virtual T operator+(const T& other) const = 0;
    virtual T operator*(const T& other) const = 0;
    virtual T operator-() const = 0;
    virtual T operator/(const T& other) const = 0;

    T operator-(const T &other) const;

    T operator%(const T &other) const;
    T gcd(const T &other) const;
    T lcm(const T &other);

    virtual ~Integral() = default;
};

template <class T> 
T Integral<T>::operator-(const T &other) const {
  return operator+(-other);
}

template <class T> 
T Integral<T>::operator%(const T &other) const {
  return *this - other * (*this / other);
}

template <class T> 
T Integral<T>::gcd(const T &other) const {
  if(*this == T(0) || other == T(0)){
    return T(0);
  }
  T a = static_cast<const T &>(*this);
  T b = other;
  while (b > T(0)) {
    T r = a % b;
    a = b;
    b = r;
  }
  return a;
}

template <class T> 
T Integral<T>::lcm(const T &other) {
  return *this * other / gcd(other);
}
