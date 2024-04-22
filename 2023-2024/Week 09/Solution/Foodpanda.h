#pragma once
#include "Restaurant.h"

class Foodpanda
{
	Restaurant* restaurants;
	unsigned restaurantsCapacity;
	unsigned restaurantsCount;

	void free();
	void copyFrom(const Foodpanda& other);
	void moveFrom(Foodpanda&& other);

	void resize();
	bool thisRestaurantExists(const char* restaurantName, int& id) const;
public:
	Foodpanda();
	Foodpanda(const Foodpanda& other);
	Foodpanda(Foodpanda&& other);
	Foodpanda(unsigned capacity);
	Foodpanda& operator=(const Foodpanda& other);
	Foodpanda& operator=(Foodpanda&& other);
	~Foodpanda();

	void addProductToARestaurant(const MyString& name, const MyString& product);
	void addProductToARestaurant(const MyString& name, MyString&& product);

	void addRestaurant(const Restaurant& rest);
	void addRestaurant(Restaurant&& rest);

	void addOrder(const MyString& name, const Order& order);
	void addOrder(const MyString& name, Order&& order);
};

