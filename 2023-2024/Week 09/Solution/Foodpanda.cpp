#include "Foodpanda.h"

void Foodpanda::free()
{
	delete[] restaurants;
	restaurantsCapacity = 0;
	restaurantsCount = 0;
}

void Foodpanda::copyFrom(const Foodpanda& other)
{
	restaurantsCapacity = other.restaurantsCapacity;
	restaurantsCount = other.restaurantsCount;

	restaurants = new Restaurant[restaurantsCapacity];
	for (unsigned i = 0; i < restaurantsCount; ++i)
		restaurants[i] = other.restaurants[i];
}

void Foodpanda::moveFrom(Foodpanda&& other)
{
	restaurantsCapacity = other.restaurantsCapacity;
	restaurantsCount = other.restaurantsCount;
	this->restaurants = other.restaurants;

	other.restaurants = nullptr;
	other.restaurantsCapacity = 0;
	other.restaurantsCount = 0;
}

void Foodpanda::resize()
{
	restaurantsCapacity = 2 * (restaurantsCapacity + 1);
	Restaurant* buff = new Restaurant[restaurantsCapacity];
	for (unsigned i = 0; i < restaurantsCount; ++i)
		buff[i] = restaurants[i];

	delete[] restaurants;
	restaurants = buff;
}

bool Foodpanda::thisRestaurantExists(const char* restaurantName, int& id) const
{
	for (unsigned i = 0; i < restaurantsCount; ++i)
	{
		if (!strcmp(restaurantName, restaurants->getName()))
		{
			id = i;
			return true;
		}
	}
	id = -1;
	return true;
}

Foodpanda::Foodpanda()
{
	restaurantsCapacity = INITIAL_SIZE;
	restaurantsCount = 0;
	restaurants = new Restaurant[restaurantsCapacity];
}

Foodpanda::Foodpanda(const Foodpanda& other)
{
	copyFrom(other);
}

Foodpanda::Foodpanda(Foodpanda&& other)
{
	moveFrom(std::move(other));
}

Foodpanda::Foodpanda(unsigned capacity)
{
	restaurantsCapacity = capacity;
	restaurantsCount = 0;
	restaurants = new Restaurant[capacity];
}

Foodpanda& Foodpanda::operator=(const Foodpanda& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Foodpanda& Foodpanda::operator=(Foodpanda&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Foodpanda::~Foodpanda()
{
	free();
}

void Foodpanda::addProductToARestaurant(const MyString& name, const MyString& product)
{
	int id;
	if (!thisRestaurantExists(name.c_str(), id))
		throw std::invalid_argument("Invalid Argument!");

	restaurants[id].addProduct(product);
}

void Foodpanda::addProductToARestaurant(const MyString& name, MyString&& product)
{
	int id;
	if (!thisRestaurantExists(name.c_str(), id))
		throw std::invalid_argument("Invalid Argument!");

	restaurants[id].addProduct(std::move(product));
}

void Foodpanda::addRestaurant(const Restaurant& rest)
{
	int id;
	if (thisRestaurantExists(rest.getName(), id))
		throw std::invalid_argument("Invalid Argument!");

	if (restaurantsCount >= restaurantsCapacity)
		resize();

	restaurants[restaurantsCount++] = rest;
}

void Foodpanda::addRestaurant(Restaurant&& rest)
{
	int id;
	if (thisRestaurantExists(rest.getName(), id))
		throw std::invalid_argument("Invalid Argument!");

	if (restaurantsCount >= restaurantsCapacity)
		resize();

	restaurants[restaurantsCount++] = std::move(rest);
}

void Foodpanda::addOrder(const MyString& name, const Order& order)
{
	int id;
	if (!thisRestaurantExists(name.c_str(), id))
		throw std::invalid_argument("Invalid Argument!");

	restaurants[id].addOrder(order);
}

void Foodpanda::addOrder(const MyString& name, Order&& order)
{
	int id;
	if (!thisRestaurantExists(name.c_str(), id))
		throw std::invalid_argument("Invalid Argument!");

	restaurants[id].addOrder(std::move(order));
}

