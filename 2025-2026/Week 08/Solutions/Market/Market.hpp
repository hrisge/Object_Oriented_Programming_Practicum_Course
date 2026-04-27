#pragma once
#include "Array.hpp"
#include "Item.hpp"

// ще ни трябва Г4 за Market, защото той ще заделя памет за продуктите
class Market {
	Array<Item> items;
public:
	Market();
	Market(const Market& other) = delete;
	Market& operator=(const Market&) = delete;
	~Market();

	
	const Array<Item>& getItems() const;

	void addProduct(const Product& p);
	void removeProduct(const Product& p);
	void buyProduct(const Product& p, unsigned count);
	void sellProduct(const Product& p, unsigned count);
	int receivingTimeFor(const Product& p, unsigned count) const;
};