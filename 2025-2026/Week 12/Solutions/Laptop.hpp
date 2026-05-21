#pragma once

#include "Computer.hpp"
#include <iostream>
class Laptop : public Computer {

public:
  void printType() const override;
  std::string peripherals() const override;
};
