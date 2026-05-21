#pragma once

#include "Directory.hpp"
#include "PrintCommand.hpp"
#include "PrintPathCommand.hpp"
#include <ostream>

class PrintTreeFromDirecoryCommand : public PrintCommand {
  const Directory& dir;
  // рекурсивно обхождаме дървото и принтираме всеки запис
  void printTreeHelper(const Entry& entry){
    if(entry.getType() == 'D'){
      const Directory& dir = (const Directory&)entry; 
      for(const Entry* e : dir.allEntries()){
        PrintPathCommand(*e, out).execute();
        out << '\n';
        printTreeHelper(*e);
      }
    }
    else{
      return;
    }
  }

public:
  void undo() override {
    return;
  }

  PrintTreeFromDirecoryCommand(const Directory &dir, std::ostream& out = std::cout) : dir(dir), PrintCommand(out) {}
  void execute() override {
    printTreeHelper(dir);
  }
};
