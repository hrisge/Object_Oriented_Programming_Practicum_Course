#pragma once
#include "Integral.hpp"

template <unsigned P>
class RemainderOf : public Integral<RemainderOf<P>> {
    unsigned remainder;
    unsigned power(unsigned base, unsigned p) const;

  public:
    RemainderOf();
    RemainderOf(unsigned number);
    RemainderOf operator+(const RemainderOf<P> &other) const override;
    RemainderOf operator-() const override;
    using Integral<RemainderOf<P>>::operator-;
    RemainderOf operator*(const RemainderOf<P> &other) const override;
    RemainderOf operator/(const RemainderOf<P> &other) const override;
    int toInt() const override;
    RemainderOf fromInt(int number) const override;
    bool lessThan(const RemainderOf<P> &other) const override;
    void serialize(std::ostream &out) const override;
};

template <unsigned int P>
unsigned RemainderOf<P>::power(unsigned base, unsigned p) const {
  if (p == 0)
    return 1;
  else if (p % 2 == 0)
    return power((base * base) % P, p / 2);
  else
    return (base * power(base, p - 1)) % P;
}

template <unsigned int P> 
RemainderOf<P>::RemainderOf() : remainder(0) {}
template <unsigned int P>
RemainderOf<P>::RemainderOf(unsigned number) : remainder(number % P) {}
template <unsigned int P>
RemainderOf<P> RemainderOf<P>::operator+(const RemainderOf<P> &other) const {
  return (remainder + other.remainder) % P;
}
template <unsigned int P> RemainderOf<P>  RemainderOf<P>::operator-() const {
  return P - remainder;
}
template <unsigned int P>
RemainderOf<P> RemainderOf<P>::operator*(const RemainderOf<P> &other) const {
  return (remainder * other.remainder) % P;
}
template <unsigned int P>
RemainderOf<P> RemainderOf<P>::operator/(const RemainderOf<P> &other) const {
  return (remainder * power(other.remainder, P - 2)) % P;
}
template <unsigned int P> 
int RemainderOf<P>::toInt() const {
  return remainder;
}
template <unsigned int P>
RemainderOf<P>  RemainderOf<P>::fromInt(int number) const {
  return RemainderOf(number);
}
template <unsigned int P>
bool RemainderOf<P>::lessThan(const RemainderOf<P> &other) const {
  return remainder < other.remainder;
}
template <unsigned int P>
void RemainderOf<P>::serialize(std::ostream &out) const {
  out << remainder;
}
