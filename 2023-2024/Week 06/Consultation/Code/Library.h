#pragma once
#include "Book.h"
#include "Bitset/Bitset.h"

const constexpr int MAX_BOOKS = 1024;

class Library {
private:
    Book books[MAX_BOOKS];
    int currSize = 0;
    Bitset isAvailable;

public:
    void returnBook(const Book& book);
    const Book* borrowBook(const char* name);

    void addBook(const Book& book);
    void removeBook(const Book& book);


    void saveBooks(const char *filePath) const;
    void loadBooks(const char* filePath);
private:
    int findBookByName(const char* name) const;
};

