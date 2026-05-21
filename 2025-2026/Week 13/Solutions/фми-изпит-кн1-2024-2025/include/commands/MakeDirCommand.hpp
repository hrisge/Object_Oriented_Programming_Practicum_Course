#pragma once

#include "Command.hpp"
#include "Directory.hpp"
class MakeDirCommand : public Command{
  Directory& parentDir;
  std::string name;
  bool executed;
public:
  void undo() override {
    if(!executed) return;
    parentDir.removeEntry(name);
    executed = false;
  }

  MakeDirCommand(Directory &parentDir, const std::string& name) : parentDir(parentDir), name(name), executed(false) {}
  MakeDirCommand(Directory& parentDir, const Directory& dir) : parentDir(parentDir), name(dir.name()), executed(false) {}
  void execute() override {
    if(executed) return;
    parentDir.addEntry(Directory(name));
    executed = true;
  }
};