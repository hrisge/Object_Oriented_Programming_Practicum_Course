#pragma once
#include "ShoppingCart.hpp"

class User {
	char name[101];
	double money;
	// тъй като ShoppingCart няма default конструктор, трябва да пазим масив от указатели 
	Array<ShoppingCart*> carts;
	Market& market;

public:

	User(const char* name, double money, Market& market);
	User(const User&) = delete;
	User& operator=(const User&) = delete;
	~User() {
		for (ShoppingCart* s: carts) {
			delete s;
		}
	}

	void addCart(const char* name);
	void renameCart(ShoppingCart& cart, const char* newName);

	ShoppingCart& find(const std::function<bool(const ShoppingCart&)>& f);
	const ShoppingCart& find(const std::function<bool(const ShoppingCart&)>& f) const;

	ShoppingCart& maxByPrice();
	const ShoppingCart& maxByPrice() const;
	ShoppingCart& minByPrice();
	const ShoppingCart& minByPrice() const;
	ShoppingCart& maxByDeliveryTime();
	const ShoppingCart& maxByDeliveryTime() const;
	ShoppingCart& minByDeliveryTime();
	const ShoppingCart& minByDeliveryTime() const;
	ShoppingCart& maxByCount();
	const ShoppingCart& maxByCount() const;
	ShoppingCart& minByCount();
	const ShoppingCart& minByCount() const;

	User& sortByPrice();
	User& sortByDeliveryTimeAscending();
	User& sortByDeliveryTimeDescending();
	User& sortByCount();

	User& filterByPriceRange(double begin, double end);
	User& filterByDeliveryTimeRange(int begin, int end);
	User& filterByCountRange(size_t begin, size_t end);

	User& addToAllCarts(const Product& product);

	const Product& maxProductByPrice() const;
	const Product& minProductByPrice() const;
	const Product& maxProductByDeliveryTime() const;
	const Product& minProductByDeliveryTime() const;
};