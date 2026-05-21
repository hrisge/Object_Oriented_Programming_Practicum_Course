#pragma once

#include "Directory.hpp"
#include "PrintCommand.hpp"
#include "PrintPathCommand.hpp"

class PrintChildrenCommand : public PrintCommand{
    const Directory& dir;

  public:
    void undo() override {
      return;
    }

  PrintChildrenCommand(const Directory &dir, std::ostream& out = std::cout) : dir(dir), PrintCommand(out) {}
  void execute() override {
    for (const Entry *e : dir.allEntries()) {
      PrintPathCommand(*e, out).execute();
      out << '\n';
    }
  }
};