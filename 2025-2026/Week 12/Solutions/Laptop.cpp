#include "Laptop.hpp"

void Laptop::printType() const { std::cout << "Laptop"; }
std::string Laptop::peripherals() const {
  return "mousepad, keyboard, monitor";
}
