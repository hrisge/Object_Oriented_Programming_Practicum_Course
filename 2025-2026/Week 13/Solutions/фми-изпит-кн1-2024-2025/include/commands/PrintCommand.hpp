#pragma once

#include "Command.hpp"
#include <iostream>
class PrintCommand : public Command{
protected:
    std::ostream& out;
public:
    PrintCommand(std::ostream& out = std::cout) : out(out) {}
};