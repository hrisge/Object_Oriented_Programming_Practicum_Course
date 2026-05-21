#pragma once

#include "Entry.hpp"
#include <ostream>
class Note : public Entry{
    std::string content;

public:
  Note(const std::string& name) : Entry(name) {}
  Note(const std::string& name, const std::string& content) 
  : Entry(name), content(content) {}

  const std::string& getContent() const {
    return content;
  }
  void setContent(const std::string& content){
    this->content = content;
  }
  size_t size() const override {
    return content.size();
  }
  std::ostream& serialize(std::ostream& out) const override {
    printPath(out);
    out << ", " << name() << ", " << getType() << ", " << content;
    return out;
  }
  char getType() const override{
    return 'F';
  }
  Note* clone() const override { return new Note(*this);}
};