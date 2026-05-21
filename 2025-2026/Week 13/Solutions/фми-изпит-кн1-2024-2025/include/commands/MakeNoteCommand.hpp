#pragma once

#include "Command.hpp"
#include "Directory.hpp"
#include "Note.hpp"
class MakeNoteCommand : public Command {
  Directory& dir;
  std::string name;
  std::string content;
  bool executed;
public:
  MakeNoteCommand(Directory &dir, const std::string& name, const std::string& content)
      : dir(dir), name(name), content(content), executed(false) {}
  MakeNoteCommand(Directory& dir, const Note& note) 
  : dir(dir), name(note.name()), content(note.getContent()), executed(false) {}
  void execute() override {
    if(executed) return;
    dir.addEntry(Note(name, content));
    executed = true;
  }

  void undo() override {
    if(!executed) return;
    dir.removeEntry(name);
    executed = false;
  }
};