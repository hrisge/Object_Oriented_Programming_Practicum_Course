#include "ChangeDirCommand.hpp"
#include "Directory.hpp"
#include "MakeDirCommand.hpp"
#include "MakeNoteCommand.hpp"
#include "Note.hpp"
#include "PrintChildrenCommand.hpp"
#include "PrintPathCommand.hpp"
#include "PrintTreeCommand.hpp"
#include "PrintTreeFromDirectoryCommand.hpp"
#include "RemoveEntryCommand.hpp"
#include "FileSystem.hpp"
#include <cassert>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

// В тестовете по-долу ще използваме stringstream, за да симулираме стандартния вход и изход
// stringstream може да извършва входно-изходни операции върху низ по същия начин както сме свикнали
// с потоците за вход и изход, защото наследява std::istream и std::ostream, подобно на fstream

TEST_CASE("Directory - Create"){
    Directory d("directory");
    CHECK_EQ(d.name(), "directory");
    CHECK_EQ(d.size(), 0);
    CHECK_EQ(d.hasParent(), false);
    CHECK_THROWS(d.getEntry(""));
    SUBCASE("Serialize"){
        std::stringstream ss;
        d.serialize(ss);
        CHECK_EQ(ss.str(), "/, directory, D, ");
    }
    
}

TEST_CASE("Directory - Copy"){
    Directory d("directory");
    SUBCASE("Copy Constructor"){
        Directory d2(d);
        CHECK_EQ(d.name(), d2.name());
        CHECK_EQ(d.size(), d2.size());
        CHECK_EQ(d.hasParent(), d2.hasParent());
        SUBCASE("Serialize Clone"){
            std::stringstream ss1;
            std::stringstream ss2;
            d.serialize(ss1);
            d2.serialize(ss2);
            CHECK_EQ(ss1.str(), ss2.str());
        }
    }
    SUBCASE("Operator="){
        Directory d2("name");
        d2 = d;
        CHECK_EQ(d.name(), d2.name());
        CHECK_EQ(d.size(), d2.size());
        CHECK_EQ(d.hasParent(), d2.hasParent());
        SUBCASE("Serialize Clone"){
            std::stringstream ss1;
            std::stringstream ss2;
            d.serialize(ss1);
            d2.serialize(ss2);
            CHECK_EQ(ss1.str(), ss2.str());
        }
    }
    SUBCASE("Clone"){
        Directory* dClone(d.clone());
        CHECK_EQ(d.name(), dClone->name());
        CHECK_EQ(d.size(), dClone->size());
        CHECK_EQ(d.hasParent(), dClone->hasParent());
        SUBCASE("Serialize Clone"){
            std::stringstream ss1;
            std::stringstream ss2;
            d.serialize(ss1);
            dClone->serialize(ss2);
            CHECK_EQ(ss1.str(), ss2.str());
        }
        delete dClone;
    }
    
}

TEST_CASE("Note - Create"){
    SUBCASE("Default Constructor"){
        Note n("note");
        CHECK_EQ(n.size(), 0);
        CHECK_EQ(n.name(), "note");
        CHECK_EQ(n.getContent(), std::string());
        CHECK_EQ(n.hasParent(), false);
    }
    SUBCASE("Parametrized Constructor"){
        std::string content = "content";
        Note n("note", content);
        CHECK_EQ(n.size(), content.length());
        CHECK_EQ(n.name(), "note");
        CHECK_EQ(n.getContent(), content);
        CHECK_EQ(n.hasParent(), false);
    }
    
}

TEST_CASE("Note - Set Content"){
    Note n("note");
    n.setContent("content");
    CHECK_EQ(n.getContent(), "content");
}

TEST_CASE("Note - Size"){
    std::string content = "content";
    Note n("note", content);
    CHECK_EQ(n.size(), content.length());
    content = "different content";
    n.setContent(content);
    CHECK_EQ(n.size(), content.length());
}

TEST_CASE("Entry - Set Parent"){
    Entry* e = new Directory("entry");
    SUBCASE("Directory Parent"){
        Directory parent("parent");
        e->setParent(parent);
        CHECK_EQ(&e->getParent(), &parent);
        CHECK(e->hasParent());
    }
    SUBCASE("Note Parent"){
        Note parent2("parent2");
        CHECK_THROWS(e->setParent(parent2));
        
    }
    delete e;
}

TEST_CASE("Directory - Add Entry"){
    Directory d("root");
    std::stringstream ss;
    SUBCASE("Add Directory"){
        Directory child("child");
        d.addEntry(child);
        CHECK_NOTHROW(d.getEntry("child"));
        CHECK_EQ(d.size(), 0);
        Directory& childRef = static_cast<Directory&>(d.getEntry("child"));

        CHECK_EQ(&childRef.getParent(), &d);

        childRef.serialize(ss);
        CHECK_EQ(ss.str(), "/root, child, D, ");
    }
    SUBCASE("Add Note"){
        Note child("child");
        d.addEntry(child);
        CHECK_NOTHROW(d.getEntry("child"));
        CHECK_EQ(d.size(), 0);
        Note& childRef = static_cast<Note&>(d.getEntry("child"));

        CHECK_EQ(&childRef.getParent(), &d);

        childRef.serialize(ss);
        CHECK_EQ(ss.str(), "/root, child, F, ");
    }
}

TEST_CASE("Directory - Remove Entry"){
    Directory d("root");
    Directory child("child");
    d.addEntry(child);
    d.removeEntry("child");

    CHECK_THROWS(d.getEntry("child"));
}

TEST_CASE("Directory - Size"){
    Directory d("root");
    d.addEntry(Directory("child"));
    Directory& childRef = static_cast<Directory&>(d.getEntry("child"));
    std::stringstream ss;

    SUBCASE("Add Empty Note"){
        Note note("note");
        childRef.addEntry(note);
        CHECK_EQ(childRef.size(), 0);
        CHECK_EQ(d.size(), 0);
        CHECK_EQ(childRef.getEntry("note").size(), 0);
        note = static_cast<const Note&>(childRef.getEntry("note"));
        note.serialize(ss);
        CHECK_EQ(ss.str(), "/root/child, note, F, ");
    }
    SUBCASE("Add Note with Content"){
        std::string content = "content";
        Note note("note", content);
        childRef.addEntry(note);
        CHECK_EQ(childRef.getEntry("note").size(), content.size());
        
        CHECK_EQ(childRef.size(), content.size());
        CHECK_EQ(d.size(), content.size());
        
        note = static_cast<const Note&>(childRef.getEntry("note"));
        note.serialize(ss);
        CHECK_EQ(ss.str(), "/root/child, note, F, content");    
        ss = std::stringstream();
        SUBCASE("Change Note Content"){
            content = "bigger content";
            Note& noteRef = static_cast<Note&>(childRef.getEntry("note"));
            noteRef.setContent(content);
            noteRef.serialize(ss);
            CHECK_EQ(childRef.getEntry("note").size(), content.size());
            CHECK_EQ(childRef.size(), content.size());
            CHECK_EQ(d.size(), content.size());
            CHECK_EQ(ss.str(), "/root/child, note, F, bigger content");   
        }
        SUBCASE("Add Second Note"){
            Note note2("note2", "different content");
            childRef.addEntry(note2);
            CHECK_EQ(childRef.size(), note.size() + note2.size());
            CHECK_EQ(d.size(), note.size() + note2.size());
        }
        SUBCASE("Add a Lot of Nodes"){
            int size = 0;
            for(int i = 0; i < 100 ; i++){
                std::string name = "n";
                name.append(std::to_string(i));
                size += std::to_string(i).length();
                childRef.addEntry(Note(name, std::to_string(i)));
            }
            CHECK_EQ(childRef.size(), size + note.size());
        }
    }
}

Directory createTree(){
    Directory root("root");
    root.addEntry(Directory("home"));
    root.addEntry(Directory("notes"));
    root.addEntry(Directory("stuff"));
    root.addEntry(Note("first note", "this is my first note"));
    Directory& home = (Directory&)root.getEntry("home");
    Directory& notes = (Directory&)root.getEntry("notes");
    Directory& stuff = (Directory&)root.getEntry("stuff");

    home.addEntry(Directory("folder"));
    notes.addEntry(Note("my note", "hello world"));
    notes.addEntry(Note("test", "test"));
    notes.addEntry(Note("random letters", "asdfghjklkoiuytredsfghjnkiuytrfghj"));
    stuff.addEntry(Directory("smaller stuff"));
    stuff.addEntry(Note("readme", "nothing to see here"));

    return root;
}

TEST_CASE("PrintPathCommand"){
    Directory d = createTree();
    std::stringstream ss;
    SUBCASE("Print Root"){
        PrintPathCommand(d, ss).execute();
        CHECK_EQ(ss.str(), "/, root, D, ");
    }
    SUBCASE("Print Child"){
        PrintPathCommand(d.getEntry("notes"), ss).execute();
        CHECK_EQ(ss.str(), "/root, notes, D, ");
    }
    SUBCASE("Print Note"){
        PrintPathCommand(d.getEntry("first note"), ss).execute();
        CHECK_EQ(ss.str(), "/root, first note, F, this is my first note");
    }
    
}

TEST_CASE("PrintChildrenCommand"){
    Directory d = createTree();
    std::stringstream ss;
    PrintChildrenCommand(d,ss).execute();
    CHECK_EQ(ss.str(), "/root, home, D, \n/root, notes, D, \n/root, stuff, D, \n/root, first note, F, this is my first note\n");
}

TEST_CASE("PrintTreeFromDirectoryCommand"){
    Directory d = createTree();
    std::stringstream ss;
    PrintTreeFromDirecoryCommand((Directory&)d.getEntry("stuff"), ss).execute();
    CHECK_EQ(ss.str(), "/root/stuff, smaller stuff, D, \n/root/stuff, readme, F, nothing to see here\n");
}

TEST_CASE("PrintTreeCommand"){
    Directory d = createTree();
    std::stringstream ss1;
    std::stringstream ss2;

    PrintTreeCommand((const Directory&)d.getEntry("notes"), ss1).execute();
    PrintTreeFromDirecoryCommand(d, ss2).execute();

    CHECK_EQ(ss1.str(), ss2.str());
}

TEST_CASE("MakeDirCommand"){
    Directory d = createTree();
    MakeDirCommand c = MakeDirCommand(d, "newDir");
    c.execute();
    CHECK_NOTHROW(d.getEntry("newDir"));
    c.undo();
    CHECK_THROWS(d.getEntry("newDir"));
}

TEST_CASE("MakeNoteCommand"){
    Directory d = createTree();
    MakeNoteCommand c = MakeNoteCommand(d, "newNote", "content");
    c.execute();
    CHECK_NOTHROW(d.getEntry("newNote"));
    c.undo();
    CHECK_THROWS(d.getEntry("newNote"));
}

TEST_CASE("RemoveEntryCommand"){
    Directory d = createTree();
    Note n("newNote", "content");
    MakeNoteCommand c = MakeNoteCommand(d, n);
    c.execute();
    RemoveEntryCommand r = RemoveEntryCommand(d, "newNote");
    r.execute();
    CHECK_THROWS(d.getEntry("newNote"));
    r.undo();
    CHECK_NOTHROW(d.getEntry("newNote"));
    Note& newNoteRef = static_cast<Note&>(d.getEntry("newNote"));
    CHECK_EQ(newNoteRef.name(), n.name());
    CHECK_EQ(newNoteRef.getContent(), n.getContent());
}

TEST_CASE("ChangeDirCommand"){
    Directory* dPos = new Directory(createTree());
    ChangeDirCommand c = ChangeDirCommand(dPos, static_cast<Directory&>(dPos->getEntry("stuff")));
    c.execute();
    CHECK_EQ(dPos->name(), "stuff");
    c.undo();
    CHECK_EQ(dPos->name(), "root");
    delete dPos;
}

TEST_CASE("FileSystef - Consecutive Undo"){
    Directory d = createTree();
    FileSystem fs(d);
    fs.removeEntry("stuff");
    fs.makeDir("newDir");
    fs.changeDir("newDir");
    fs.makeNote("Note", "");
    fs.makeDir("otherDir");
    fs.changeDir("otherDir");
    std::stringstream ss;
    fs.printCurrentPath(ss);
    CHECK_EQ(ss.str(), "/root/newDir, otherDir, D, ");
    while(fs.canUndo()){
        fs.undo();
    }
    ss = std::stringstream();
    std::stringstream ss1;

    fs.printTreeFromRoot(ss);
    PrintTreeCommand(d, ss1).execute();

    // тъй като undo не запазва подредбата на записите, ще сортираме
    // резултатите и ще проверим дали съвпадат 
    std::vector<std::string> lines1;
    std::string line;
    //std::readline чете от поток за вход докато не стигне /n и записва в низ
    while (std::getline(ss, line)) {
        lines1.push_back(line);
    }
    std::vector<std::string> lines2;
    while (std::getline(ss1, line)) {
        lines2.push_back(line);
    }

    sort(lines1.begin(), lines1.end(), [](std::string a, std::string b){return strcmp(a.c_str(), b.c_str()) < 0;});
    sort(lines2.begin(), lines2.end(), [](std::string a, std::string b){return strcmp(a.c_str(), b.c_str()) < 0;});

    CHECK_EQ(lines1, lines2);
}