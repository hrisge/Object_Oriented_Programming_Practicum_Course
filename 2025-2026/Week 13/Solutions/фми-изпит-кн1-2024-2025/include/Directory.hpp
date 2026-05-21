#pragma once

#include "Entry.hpp"
#include <stdexcept>
#include <vector>
// Директорията представлява дървовидна структура, така че ще използваме рекурсия за да я обработваме
class Directory : public Entry{
    std::vector<Entry*> entries;

    void copy(const Directory& other){
        for(const Entry* e : other.entries){
            addEntry(*e->clone());
        }
    }

    void free(){
        for(Entry* e : entries){
            delete e;
        }
    }
public:
    std::ostream &serialize(std::ostream &out) const override {
      printPath(out);
      out << ", " << name() << ", " << getType() << ", ";
      return out;
    }

  Directory(const std::string& name) : Entry(name) {}

  
  Directory(const Directory& other) : Entry(other){
    copy(other);
  }

  Directory& operator=(const Directory& other){
    if(this == &other) return *this;
    free();
    Entry::operator=(other);
    copy(other);
    return *this;
  }

  ~Directory() override {free();}

  char getType() const override {
    return 'D';
  }


  void addEntry(const Entry& entry){
    Entry* newEntry = entry.clone();
    newEntry->setParent(*this);
    entries.push_back(newEntry);
  }

  void removeEntry(const std::string& name){
    for(std::vector<Entry*>::iterator i = entries.begin(); i != entries.end(); ++i){
      if((*i)->name() == name){
        delete *i;
        entries.erase(i);
        return;
      }
    }
  }

  const Entry& getEntry(const std::string& name) const{
    for(const Entry* e : entries){
      if(e->name() == name) return *e;
    }
    throw std::runtime_error("no entry with that name");
  }

  Entry& getEntry(const std::string& name){
    for(Entry* e : entries){
      if(e->name() == name) return *e;
    }
    throw std::runtime_error("no entry with that name");
  }

  const std::vector<Entry*>& allEntries() const{
    return entries;
  }

  size_t size() const override {
    size_t result = 0;
    for(const Entry* e : entries){
        result += e->size();
    }
    return result;
  }
  Directory* clone() const override {return new Directory(*this);}
};