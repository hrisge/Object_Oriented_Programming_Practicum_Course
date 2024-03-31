#pragma once
#include <fstream>

enum class Genre : char {
    SciFi,
    Drama,
    Romance
};

const int ISBN_LENGTH = 14;

class Book {
private:
    char ISBN[ISBN_LENGTH];
    char* name = nullptr;
    char* content = nullptr;
    int yearOfCreation = 1970;
    Genre genre;
public:

    Book() = default;
    Book(const Book& other);
    Book& operator=(const Book& other);
    ~Book();

    const char* getName() const;
    Genre getGenre() const;
    int getYearOfCreation() const;
    const char* getISBN() const;
    const char* getContent() const;

    void setISBN(const char* newISBN);
    void setName(const char* newName);
    void setContent(const char* newContent);
    void setYearOfCreation(int newYearOfCreation);
    void setGenre(Genre newGenre);

    void saveBook(std::ofstream&  ofs) const;
    friend Book readBook(std::ifstream& ifs);

private:
    void free();
    void copyFrom(const Book& other);
};

Book readBook(std::ifstream& ifs);