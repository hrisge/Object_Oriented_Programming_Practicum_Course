#include "Book.h"
#include <cstring>

Book::Book(const Book& other) {
    copyFrom(other);
}

Book& Book::operator=(const Book& other) {

    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Book::~Book() {
    free();
}

void Book::free() {
    delete[] name;
    delete[] content;
    name = content = nullptr;
    yearOfCreation = 0;
    ISBN[0] = '\0';
}
void Book::copyFrom(const Book& other) {
    name = new char [strlen(other.name) + 1];
    strcpy(name, other.name);

    content = new char[strlen(other.content) + 1];
    strcpy(content, other.content);

    yearOfCreation = other.yearOfCreation;
    genre = other.genre;
    strcpy(ISBN, other.ISBN);
}

void Book::setISBN(const char* newISBN) {
    if (strlen(newISBN) >= ISBN_LENGTH - 1) {
        return;
    }

    strcpy(ISBN, newISBN);
}
void Book::setName(const char* newName) {
    if (newName == nullptr || newName == name) {
        return;
    }

    delete[] name;
    name = new char[strlen(newName) + 1];
    strcpy(name, newName);
}
void Book::setContent(const char* newContent) {
    if (newContent == nullptr || newContent == content) {
        return;
    }

    delete[] content;
    content = new char[strlen(newContent) + 1];
    strcpy(content, newContent);
}
void Book::setYearOfCreation(int newYearOfCreation) {
    if (newYearOfCreation <  -1000) {
        return;
    }

   yearOfCreation = newYearOfCreation;
}
void Book::setGenre(Genre newGenre) {
    genre = newGenre;
}

const char* Book::getName() const {
    return name;
}
Genre Book::getGenre() const {
    return genre;
}
int Book::getYearOfCreation() const {
    return yearOfCreation;
}
const char* Book::getISBN() const {
    return ISBN;
}
const char* Book::getContent() const {
    return content;
}

void Book::saveBook(std::ofstream&  ofs) const {
//    ofs.write((const char*)this, sizeof(Book));


    ofs.write((const char*)&ISBN, ISBN_LENGTH);

    int nameLen = strlen(name) + 1;
    ofs.write((const char*)&nameLen, sizeof(int));
    ofs.write(name, nameLen);

    int contentLen = strlen(content);
    ofs.write((const char*)&contentLen, sizeof(int));
    ofs.write(content, contentLen);

    ofs.write((const char*)&yearOfCreation, sizeof(int));
    ofs.write((const char*)&genre, sizeof(Genre));
};


Book readBook(std::ifstream& ifs) {
    Book book;
    ifs.read((char*)book.ISBN, ISBN_LENGTH);

    int nameLen = 0;
    ifs.read((char*)&nameLen, sizeof(int));

    book.name = new char[nameLen];
    ifs.read(book.name, nameLen);

    int contentLen = 0;
    ifs.read((char*)&contentLen, sizeof(int));

    book.content = new char[contentLen];
    ifs.read(book.content, contentLen);

    ifs.read((char*)&book.yearOfCreation, sizeof(int));
    ifs.read((char*)&book.genre, sizeof(Genre));

    return book;
}


