#pragma once

#include "Command.hpp"
#include "Directory.hpp"
class RemoveEntryCommand : public Command{
  Directory& dir;
  Entry* removedDir;
  std::string name;
  bool executed;
public:
  RemoveEntryCommand(Directory &dir, const std::string& name)
      : dir(dir), name(name), executed(false), removedDir(nullptr) {}
    
  RemoveEntryCommand(const RemoveEntryCommand&) = delete;
  RemoveEntryCommand& operator=(const RemoveEntryCommand&) = delete;
  
  void execute() override {
    if(executed) return;
    removedDir = dir.getEntry(name).clone();
    dir.removeEntry(name);
    executed = true;
  }

  void undo() override {
    if(!executed) return;
    dir.addEntry(*removedDir);
    executed = false;
  }

  ~RemoveEntryCommand() override {
    delete removedDir;
  }
};