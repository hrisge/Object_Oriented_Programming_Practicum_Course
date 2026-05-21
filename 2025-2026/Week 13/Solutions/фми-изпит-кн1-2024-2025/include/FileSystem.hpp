#pragma once

#include "ChangeDirCommand.hpp"
#include "Directory.hpp"
#include "MakeDirCommand.hpp"
#include "MakeNoteCommand.hpp"
#include "PrintTreeCommand.hpp"
#include "PrintTreeFromDirectoryCommand.hpp"
#include "RemoveEntryCommand.hpp"
#include "Stack.hpp"
#include "PrintChildrenCommand.hpp"
#include "PrintPathCommand.hpp"
#include <iostream>
#include <ostream>
#include <stdexcept>

class FileSystem{
    Directory* currentDirectory;
    Stack<Command*> prevCommands;

    void useAndStashCommand(Command* c){
      c->execute();
      prevCommands.push(c);
    }

public:
    FileSystem(const Directory& root) : currentDirectory(root.clone()) {}
    FileSystem(const FileSystem&) = delete;
    FileSystem& operator=(const FileSystem&) = delete;

    bool canUndo() const {
      return !prevCommands.empty();
    }

    void undo(){
      prevCommands.top()->undo();
      delete prevCommands.top();
      prevCommands.pop();
    }

    // обработката на грешки може да се остави и на по-горните слоеве
    void changeDir(const std::string& name){
      try{
        Entry& e = currentDirectory->getEntry(name);
        if(e.getType() == 'D'){
          useAndStashCommand(new ChangeDirCommand(currentDirectory, (Directory&)e));
        }
        else{
          std::cout << name << " is not a directory";
        }
      }
      catch(const std::runtime_error& e){
        std::cout << e.what() << std::endl;
      }
    }

    void makeDir(const std::string& name){
      useAndStashCommand(new MakeDirCommand(*currentDirectory, name));
    }

    void makeNote(const std::string& name, const std::string& content){
      useAndStashCommand(new MakeNoteCommand(*currentDirectory, name, content));
    }

    void removeEntry(const std::string& name){
      try{
        useAndStashCommand(new RemoveEntryCommand(*currentDirectory, name));
      }
      catch(const std::runtime_error& e){
        std::cout << e.what() << std::endl;
      }
    }
    // няма нужда да запазваме print-овете в стека, тъй като undo не прави нищо за тях
    void printCurrentPath(std::ostream& out = std::cout) const {
      PrintPathCommand(*currentDirectory, out).execute();
    }
    void printChildren(std::ostream& out = std::cout) {
      PrintChildrenCommand(*currentDirectory, out).execute();
    }
    void printTreeFromCurrentDirectory(std::ostream& out = std::cout) const{
      PrintTreeFromDirecoryCommand(*currentDirectory, out).execute();
    }
    void printTreeFromRoot(std::ostream& out = std::cout) const {
      PrintTreeCommand(*currentDirectory, out).execute();
    }

    ~FileSystem() {
      while(!prevCommands.empty()){
        delete prevCommands.top();
        prevCommands.pop();
      }
      delete currentDirectory;
    }
};
