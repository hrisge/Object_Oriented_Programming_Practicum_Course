#pragma once

#include "Computer.hpp"
#include <iostream>
class GamingConsole : public Computer{

public:
  void printType() const override;
  std::string peripherals() const override;
};