#pragma once

#include "Directory.hpp"
#include "PrintCommand.hpp"
#include "PrintTreeFromDirectoryCommand.hpp"
class PrintTreeCommand : public PrintCommand {
  const Directory& dir;

public:
  void undo() override {
    return;
  }

  PrintTreeCommand(const Directory& currentDirectory, std::ostream& out = std::cout) : PrintCommand(out), dir(currentDirectory) {}
  void execute() override {
    
    const Entry* parent = &dir;
    while(parent->hasParent()){
      parent = &parent->getParent();
    }

    PrintTreeFromDirecoryCommand((const Directory&)*parent, out).execute();
  }
};