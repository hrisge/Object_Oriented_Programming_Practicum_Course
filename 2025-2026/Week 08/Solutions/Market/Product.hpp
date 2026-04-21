#pragma once
#include "Delivery.hpp"
#include <iostream>
#include <cstring>

struct Size {
	double x;
	double y;
	double z;

	bool operator==(const Size& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}
};

enum Category {
	APPAREL,
	HOME,
	TECHNOLOGY,
	GROCERY,
	HEALTH,
	HARDWARE,
	_SIZE
};

class Product {
	char name[101];
	Size size;
	double weight;
	double price;
	Delivery delivery;
	Category category;
public:
	Product();
	Product(const char* name, const Size& size, double weight,
		double price, const Delivery& delivery, Category category);

	const char* getName() const;
	const Size& getSize() const;
	double getWeight() const;
	double getPrice() const;
	const Delivery& getDelivery() const;
	Category getCategory() const;

	bool operator==(const Product& other) const;
};