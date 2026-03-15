#include <iostream>
#include <fstream>

namespace BookConstants {
    const int STR_MAX_SIZE = 65;
    const int YEAR_INIT_VAL = 0;
    const double PRICE_INIT_VAL = 0.0;
}

namespace BooksListConstants {
    const int MAX_BOOKS = 100;
    const int MIN_COUNT = 0;
}

struct Book {
    char title[BookConstants::STR_MAX_SIZE] = "";
    char author[BookConstants::STR_MAX_SIZE] = "";
    int year = BookConstants::YEAR_INIT_VAL;
    double price = BookConstants::PRICE_INIT_VAL;
};

bool isValidString(const char* str) {
    if (!str || std::strlen(str) > BookConstants::STR_MAX_SIZE) {
        return false;
    }
    return true;
}

void setTitle(Book& book, const char* title) {
    if (!isValidString(title)) {
        return;
    }
    std::strcpy(book.title, title);
}
void setAuthor(Book& book, const char* author) {
    if (!isValidString(author)) {
        return;
    }
    std::strcpy(book.author, author);
}
void setYear(Book& book, int year) {
    book.year = year;
}
void setPrice(Book& book, double price) {
    if (price < 1 || price > 100) {
        return;
    }
    book.price = price;
}

const char* getTitle(const Book& book) {
    return book.title;
}
const char* getAuthor(const Book& book){
    return book.author;
}
int getYear(const Book& book){
    return book.year;
}
double getPrice(const Book& book) {
    return book.price;
}

void readBook(Book& book, std::ifstream& ifs) {
    if (!ifs.is_open()) {
        std::cout << "File could not open" << std::endl;
        return;
    }
    ifs.getline(book.title, BookConstants::STR_MAX_SIZE, ',');
    ifs.ignore();
    ifs.getline(book.author, BookConstants::STR_MAX_SIZE, ',');
    ifs.ignore();
    ifs >> book.year;
    ifs.ignore();
    ifs >> book.price;
}
void saveBook(const Book& book, std::ofstream& ofs){
    if (!ofs.is_open()) {
        std::cout << "File could not open" << std::endl;
        return;
    }
    ofs << book.title << "," << book.author << ",";
    ofs << book.year << "," << book.price << std::endl;
}

void printBook(const Book& book) {
    std::cout << "Title: " << book.title << std::endl;
    std::cout << "Author: " << book.author << std::endl;
    std::cout << "Year: " << book.year << std::endl;
    std::cout << "Price: " << book.price << std::endl;
    std::cout << std::endl;
}

struct BooksList {
    Book books[BooksListConstants::MAX_BOOKS];
    int currentCount = BooksListConstants::MIN_COUNT;
};


void readBooksFromFile(BooksList& booksList, const char* fileName) {
    std::ifstream ifs(fileName);
    if (!ifs.is_open()) {
        std::cout << "File could not open" << std::endl;
        return;
    }
    ifs >> booksList.currentCount;
    ifs.ignore();
    for (int i = 0; i < booksList.currentCount; i++) {
        readBook(booksList.books[i], ifs);
    }
    ifs.close();
}

void addBook(BooksList& booksList, const Book& book) {
    if (booksList.currentCount < BooksListConstants::MIN_COUNT) {
        booksList.books[booksList.currentCount++] = book;
    }
}

void saveBooksToFile(const BooksList& booksList, const char* fileName){
    std::ofstream ofs(fileName);
    if (!ofs.is_open()) {
        std::cout << "File could not open" << std::endl;
        return;
    }
    ofs << booksList.currentCount << std::endl;
    for (int i = 0; i < booksList.currentCount; i++) {
        saveBook(booksList.books[i], ofs);
    }
    ofs.close();
}
void printBooks(const BooksList& booksList){
    for (int i = 0; i < booksList.currentCount; i++) {
        printBook(booksList.books[i]);
    }
}