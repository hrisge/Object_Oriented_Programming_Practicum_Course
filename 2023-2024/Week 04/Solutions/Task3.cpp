#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)


const constexpr unsigned MAX_SIZE = 64;

class Game
{
	double price;
	char title[MAX_SIZE];
	bool isAvailable;

public:
	Game()
	{
		price = 0;
		strcpy(title, "");
		isAvailable = false;
	}
	Game(const char* title, double price, bool isAvailabe)
	{
		setTitle(title);
		setPrice(price);
		setAvailability(isAvailabe);
	}

	void setPrice(double price)
	{
		if (price < 0)
			this->price = 0;
		else
			this->price = price;
	}
	void setTitle(const char* title)
	{
		if (title == nullptr || strlen(title) >= 64)
			strcpy(this->title, "");
		else
			strcpy(this->title, title);
	}
	void setAvailability(bool isAvailable)
	{
		this->isAvailable = isAvailable;
	}

	const char* getTitle() const
	{
		return title;
	}
	double getPrice() const
	{
		return price;
	}
	bool getAvailable() const
	{
		return isAvailable;
	}

	bool isFree() const
	{
		return (price < 0.001 && price > -0.001);
	}
	void print() const
	{
		std::cout << "Title: " << title << std::endl << "Price: " << price << std::endl << "Is it Available: " << isAvailable << std::endl;
	}
};

class GamePlatform
{
	Game* games = nullptr;
	unsigned numberOfGames = 0;
	unsigned sizeOfGames = 0;

	bool isFull() const
	{
		return numberOfGames >= sizeOfGames;
	}
	bool isEmpty() const
	{
		return numberOfGames == 0;
	}

public:
	GamePlatform() {}
	GamePlatform(const Game* games, unsigned numberOfGames)
	{
		this->games = new Game[numberOfGames];
		this->numberOfGames = numberOfGames;
		sizeOfGames = numberOfGames;

		for (unsigned i = 0; i < numberOfGames; i++)
		{
			this->games[i].setTitle(games[i].getTitle());
			this->games[i].setPrice(games[i].getPrice());
			this->games[i].setAvailability(games[i].getAvailable());
		}
	}
	GamePlatform(unsigned size)
	{
		sizeOfGames = size;
		numberOfGames = 0;
		games = new Game[size];
	}
	~GamePlatform()
	{
		if (games != nullptr)
			delete[] games;

		numberOfGames = 0;
		sizeOfGames = 0;
	}

	bool addGame(const Game& game)
	{
		if (isFull())
			return false;

		games[numberOfGames].setTitle(game.getTitle());
		games[numberOfGames].setPrice(game.getPrice());
		games[numberOfGames].setAvailability(game.getPrice());
		numberOfGames++;
		return true;
	}
	const Game* getGame(unsigned pos) const
	{
		if (pos < numberOfGames)
			return &games[pos];

		return nullptr;
	}
	void print() const
	{
		for (unsigned i = 0; i < numberOfGames; i++)
			games[i].print();
	}
	const Game* getCheapestGame() const
	{
		if (isEmpty())
			return nullptr;

		double currMin = games[0].getPrice();
		unsigned minIndex = 0;

		for (unsigned i = 1; i < numberOfGames; i++)
		{
			if (currMin > games[i].getPrice())
			{
				currMin = games[i].getPrice();
				minIndex = i;
			}
		}

		return &games[minIndex];
	}
	const Game* getMostExpensiveGame() const
	{
		if (isEmpty())
			return nullptr;

		double currMax = games[0].getPrice();
		unsigned maxIndex = 0;

		for (unsigned i = 1; i < numberOfGames; i++)
		{
			if (currMax < games[i].getPrice())
			{
				currMax = games[i].getPrice();
				maxIndex = i;
			}
		}

		return &games[maxIndex];
	}
	void printAllFreeGames() const
	{
		if (isEmpty())
			return;

		for (unsigned i = 0; i < numberOfGames; i++)
		{
			if (games[i].getPrice() == 0)
				games[i].print();
		}
	}
	void removeGameAtPos(unsigned pos)
	{
		if (pos >= numberOfGames)
			return;

		for (unsigned i = pos; i < numberOfGames - 1; i++)
		{
			games[i].setTitle(games[i + 1].getTitle());
			games[i].setPrice(games[i + 1].getPrice());
			games[i].setAvailability(games[i + 1].getAvailable());
		}
		numberOfGames--;
	}

	//Must be added read and write functions
};


int main()
{

}