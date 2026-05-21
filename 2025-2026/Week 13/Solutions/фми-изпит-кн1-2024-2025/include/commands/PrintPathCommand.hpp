#pragma once

#include "Entry.hpp"
#include "PrintCommand.hpp"
#include <iostream>
#include <ostream>
class PrintPathCommand : public PrintCommand{
    const Entry& entry;

  public:
    void undo() override {
      return;
    }

  PrintPathCommand(const Entry& entry, std::ostream& out = std::cout) : entry(entry), PrintCommand(out) {}
  void execute() override {
    entry.serialize(out);
  }
};