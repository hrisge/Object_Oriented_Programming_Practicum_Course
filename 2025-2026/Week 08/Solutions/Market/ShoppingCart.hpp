#pragma once
#include "Item.hpp"
#include "Array.hpp"
#include "Market.hpp"

class ShoppingCart {

	char name[101];

	// ще използваме Array, за да реализираме функционалностите, които се изискват
	Array<Item> products;

	Market* market;
	Item& find(const std::function<bool(const Item&)>& f);
	ShoppingCart(Array<Item> products, Market& market);

public:
	ShoppingCart(const char* name, Market& market);

	const char* getName() const;
	void setName(const char* name);
	double getPrice() const;
	size_t getCount() const;
	int getDeliveryTime() const;

	void addProduct(const Product& p);
	void removeProduct(const Product& p);
	void addCount(const Product& p, unsigned count = 1);
	void lowerCount(const Product& p, unsigned count = 1);

	const Item& find(const std::function<bool(const Item&)>& f) const;
	const Item& findByName(const char* name) const;

	const Item& maxByPrice() const;
	const Item& minByPrice() const;
	const Item& maxByDeliveryTime() const;
	const Item& minByDeliveryTime() const;

	void sortByPrice();
	void sortByDeliveryTimeAscending();
	void sortByDeliveryTimeDescending();
	void sortByCount();

	ShoppingCart filterByCategory(Category c) const;
	ShoppingCart filterByPriceRange(double begin, double end) const;
	ShoppingCart filterByCountRange(size_t begin, size_t end) const;
	ShoppingCart filterByDeliveryTimeRange(int begin, int end) const;

	void clear();
	void confirmOrder();
};