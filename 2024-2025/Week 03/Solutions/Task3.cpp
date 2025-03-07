#include <iostream>
#pragma warning(disable: 4996)

const constexpr unsigned TITLE_LEN = 64;
const constexpr unsigned GAMES_CAPACITY = 100;


class Game {
	double price;
	char title[TITLE_LEN];
	bool isAvailable;

public:
	Game() {
		setTitle("");
		setPrice(0);
		setIsAvailable(false);
	}
	Game(const char* title, double price, bool isAvailable) {
		setTitle(title);
		setPrice(price);
		setIsAvailable(isAvailable);
	}

	const char* getTitle() const {
		return title;
	}
	double getPrice() const {
		return price;
	}
	bool getIsAvailable() const {
		return isAvailable;
	}

	void setTitle(const char* title) {
		if (!title || strlen(title) >= TITLE_LEN)
			return;

		strcpy(this->title, title);
	}
	void setPrice(double price) {
		this->price = price;
	}
	void setIsAvailable(bool isAvailable) {
		this->isAvailable = isAvailable;
	}

	bool isFree() const {
		return getPrice() == 0;
	}
	void print() const {
		std::cout << "Title: " << getTitle() << "\nPrice:" <<
			getPrice() << "\nIs it available: ";
		if (getIsAvailable())
			std::cout << "Yes!\n";
		else
			std::cout << "No\n";
	}
};

class GamePlatform {
	Game games[GAMES_CAPACITY];
	unsigned size = 0;

	bool isEmpty() const {
		return size == 0;
	}

public:
	void addGame(const Game& game) {
		if (size >= GAMES_CAPACITY)
			return;

		games[size++] = game;
	}
	void removeGame(const char* title) {
		bool found = false;
		for (int i = 0; i < size; ++i) {
			if (!found && !strcmp(games[i].getTitle(), title))
				found = true;

			if (found) {
				games[i] = games[i + 1];
			}
		}
		size--;
	}
	void printGame(unsigned index) const {
		if (index < size)
			games[index].print();
	}
	void printAllGames() const {
		for (unsigned i = 0; i < size; ++i)
			games[i].print();
	}
	void printCheapestAndMostExpensiveGames() const {
		if (isEmpty())
			return;
	
		int cheap = 0, expensive = 0;
		for (unsigned i = 0; i < size; ++i) {
			if (games[i].getPrice() > games[expensive].getPrice())
				expensive = i;
			if (games[i].getPrice() < games[cheap].getPrice())
				cheap = i;
		}

		std::cout << "The cheapest game is: ";
		games[cheap].print();
		std::cout << "The most expensive game is: ";
		games[expensive].print();
	}
	void printAllFreeGames() const {
		for (int i = 0; i < size; ++i) {
			if (games[i].isFree())
				games[i].print();
		}
	}
};