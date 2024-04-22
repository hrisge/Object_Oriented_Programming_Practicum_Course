#pragma once
#include "Order.h"

constexpr unsigned NAME_SIZE = 26;
constexpr unsigned INITIAL_SIZE = 16;

class Restaurant
{
	char name[NAME_SIZE];
	MyString* products;
	unsigned productsCapacity;
	unsigned productsCount;
	Order* orders;
	unsigned orderCapacity;
	unsigned orderCount;

	void free();
	void copyFrom(const Restaurant& other);
	void moveFrom(Restaurant&& other);

	void resizeProducts();
	void resizeOrder();

public:
	Restaurant();
	Restaurant(const Restaurant& other);
	Restaurant(Restaurant&& other);
	Restaurant& operator=(const Restaurant& other);
	Restaurant& operator=(Restaurant&& other);
	~Restaurant();

	void addOrder(const Order& other);
	void addOrder(Order&& other);
	void addProduct(const MyString& product);
	void addProduct(MyString&& product);

	const char* getName() const;
	const MyString* getProducts() const;
	const Order* getOrders() const;
	unsigned getProductsCapaciy() const;
	unsigned getProductsCount() const;
	unsigned getOrdersCapacity() const;
	unsigned getOrdersCount() const;

	void setName(const char* name);
	void setProducts(const MyString* products, unsigned productsCount);
	void setOrders(const Order* orders, unsigned ordersCount);
	void setProducts(const MyString* products, unsigned productsCount, unsigned productsCapacity);
	void setOrders(const Order* orders, unsigned ordersCount, unsigned ordersCapacity);
};

