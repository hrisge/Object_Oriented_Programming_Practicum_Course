#pragma once

#include "Command.hpp"
#include "Directory.hpp"

class ChangeDirCommand : public Command {
  Directory*& dir;
  Directory& prev;
  Directory& next;
  bool executed;
public:
  void execute() override {
    if(executed) return;
    dir = &next;
    executed = true;
  }

  void undo() override {
    if(!executed) return;
    dir = &prev;
    executed = false;
  }

  ChangeDirCommand(Directory*& dir, Directory& next)
      : dir(dir), next(next), prev(*dir),executed(false) {}
  
};