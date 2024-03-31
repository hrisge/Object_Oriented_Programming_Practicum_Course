#include "Library.h"
#include "Bitset/Bitset.h"
#include <cstring>
#include <algorithm>


const Book* Library::borrowBook(const char* name) {
    if (!name) {
        return nullptr;
    }

    int idx = findBookByName(name);
    if (idx == -1) {
        return nullptr;
    }

    isAvailable.removeNumber(idx);
    return &books[idx];
}

int Library::findBookByName(const char *name) const {
    for(int i = 0; i < currSize; ++i) {
        if (std::strcmp(books[i].getName(), name) == 0) {
            return i;
        }
    }

    return -1;
}

void Library::returnBook(const Book& book) {
    int idx = findBookByName(book.getName());
    isAvailable.addNumber(idx);
}


void Library::addBook(const Book& book) {
    if (currSize == MAX_BOOKS) {
        return;
    }

    int idx = findBookByName(book.getName());
    if (idx != -1) {
        return;
    }

    books[currSize] = book;
    isAvailable.addNumber(currSize);
    currSize++;
}

void Library::removeBook(const Book &book) {
    int idx = findBookByName(book.getName());
    std::swap(books[idx], books[currSize]);

    if (isAvailable.hasNumber(currSize)) {
        isAvailable.addNumber(idx);
    } else {
        isAvailable.removeNumber(idx);
    }

    currSize--;
}

void Library::saveBooks(const char *filePath) const {
    if(!filePath) {
        return;
    }

    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        return;
    }

    file.write((const char*) currSize, sizeof(int));

    for (int i = 0; i <currSize ; ++i) {
        books[i].saveBook(file);
    }

    isAvailable.save(file);
    file.close();
};

void Library::loadBooks(const char *filePath) {
    if (!filePath) {
        return;
    }

    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        return;
    }

    file.read((char*)&currSize, sizeof(int));


    for (int i = 0; i < currSize; ++i) {
        books[i] = readBook(file);
    }

    isAvailable = read(file);
    file.close();
}

