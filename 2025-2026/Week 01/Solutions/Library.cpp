#include <iostream>

enum Genre {
	NOVEL,
	HISTORY,
	POETRY,
	OTHER
};

struct Book {
	char title[51];
	char author[51];
	Genre genre;
	unsigned quantity;
};

const size_t MAX_BOOKS = 1024;

struct Library {
	size_t size;
	Book books[MAX_BOOKS];
};

bool hasCapacity(const Library& l) {
	if (l.size >= MAX_BOOKS) {
		std::cout << "capacity has been reached" << std::endl;
		return false;
	}
	return true;
}

void strncopy(const char* src, char* dest, size_t n) {
	int i = 0;
	for (i = 0; src[i] != '\0' && i < n; i++) {
		dest[i] = src[i];
	}
	dest[i] = '\0';
}

size_t strlen(const char* str) {
	size_t i;
	for (i = 0; str[i] != '\0'; i++) {}
	return i;
}

Book initBook(const char* title, const char* author, Genre genre, unsigned quantity) {
	Book b;
	strncopy(title, b.title, 50);
	strncopy(author, b.author, 50);
	b.genre = genre;
	b.quantity = quantity;
	return b;
}

void addBook(Library& library, const Book& book) {
	if (hasCapacity(library)) {
		library.books[library.size] = book;
	}
}

bool streq(const char* str1, const char* str2) {
	if (strlen(str1) != strlen(str2)) return false;
	for (size_t i = 0; i < strlen(str1); i++) {
		if (str1[i] != str2[i]) return false;
	}
	return true;
}

void takeByName(Library& library, const char* title) {
	for (size_t i = 0; i < library.size; i++) {
		if (streq(library.books[i].title, title)) {
			if(library.books[i].quantity>0) library.books[i].quantity--;
			else std::cout << "Book is not in stock" << std::endl;
		}
	}
}

void returnByName(Library& library, const char* title) {
	for (size_t i = 0; i < library.size; i++) {
		if (streq(library.books[i].title, title)) {
			library.books[i].quantity++;
		}
	}
}

void printGenre(Genre genre) {
	switch (genre) {
		case Genre::HISTORY: std::cout << "History"; break;
		case Genre::NOVEL: std::cout << "Novel"; break;
		case Genre::POETRY: std::cout << "Poetry"; break;
		case Genre::OTHER: std::cout << "Other"; break;
		default: std::cout << "Invalid Genre"; break;
	}
}

void printBook(const Book& book) {
	std::cout << "Title: " << book.title << std::endl;
	std::cout << "Author: " << book.author << std::endl;
	std::cout << "Genre: ";
	printGenre(book.genre);
	std::cout << std::endl;
	std::cout << "Quantity: " << book.quantity << std::endl;
}

void printLibrary(const Library& library) {
	for (size_t i = 0; i < library.size; i++) {
		printBook(library.books[i]);
	}
}