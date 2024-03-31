#include "Member.h"
#include <cstring>

const Book* Member::getBorrowedBook() const {
    return borrowedBook;
}

Member::Member(const char *name, int memberId, Library *library) {
    strcpy(this->name, name);
    this->memberId = memberId;
    this->library = library;

}

int Member::getMemberId() const {
    return memberId;
}

void Member::setMemberId(int memberId) {
    Member::memberId = memberId;
}

void Member::borrowBook(const char *bookName) {
    if (borrowedBook) {
        return;
    }

    borrowedBook = library->borrowBook(bookName);

}

void Member::returnBook() {
    if (!borrowedBook) {
        return;
    }

    library->returnBook(*borrowedBook);
    borrowedBook = nullptr;
}
