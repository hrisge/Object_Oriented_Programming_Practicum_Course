#pragma once

#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <string>
class Entry{
    std::string m_name;
  
protected:
    std::ostream& printPath(std::ostream& out) const{
        if(!parent){
            out << "/";
            return out;
        } 
        else if(!(parent->parent)){
            out << "/" << parent->name();
            return out;
        }
        parent->printPath(out);
        out << "/" << parent->name();
        return out;
    }

    
    Entry* parent;

public:
    Entry(const std::string& name) : m_name(name), parent(nullptr) {}
    virtual size_t size() const = 0;
    const std::string& name() const {return m_name;}
    bool hasParent() const {return parent;}
    const Entry& getParent() const {return *parent;}
    Entry& getParent() {return *parent;}

    void setParent(Entry& parent){
        if(parent.getType() != 'D') throw std::runtime_error("parent has to be a directory");
        this->parent = &parent;
    }

    virtual Entry* clone() const = 0;
    virtual std::ostream& serialize(std::ostream& out) const = 0;
    virtual char getType() const = 0;
    virtual ~Entry() = default;
};