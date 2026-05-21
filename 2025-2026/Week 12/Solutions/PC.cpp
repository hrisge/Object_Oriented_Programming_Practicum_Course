#include "PC.hpp"

void PC::printType() const { std::cout << "PC"; }
std::string PC::peripherals() const {
  return "mouse, keyborad, headphones, microphone";
}
