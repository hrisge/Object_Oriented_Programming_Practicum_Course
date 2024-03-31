#pragma once

#include "Library.h"

const constexpr int MAX_MEMBER_NAME_LENGTH = 64;

class Member {
private:
    char name[MAX_MEMBER_NAME_LENGTH];
    int memberId;
    Library* library;
    const Book* borrowedBook = nullptr;

public:

    Member(const char* name, int memberId, Library* library);
    void borrowBook(const char* bookName);
    void returnBook();

    const Book* getBorrowedBook() const;
    int getMemberId() const;

    void setMemberId(int memberId);

    //Big Foyr is not needed here, as the library and borrowedBook are aggregated objects
};
