#include "Order.h"

void Order::free()
{
	delete[] products;
	productsCount = 0;
	productsCapacity = 0;
	name = "";
}

void Order::copyFrom(const Order& other)
{
	name = other.name;
	productsCount = other.productsCount;
	productsCapacity = other.productsCapacity;

	products = new MyString[productsCapacity];
	for (int i = 0; i < productsCount; i++)
		products[i] = other.products[i];
}

void Order::moveFrom(Order&& other)
{
	name = other.name;
	productsCount = other.productsCount;
	productsCapacity = other.productsCapacity;

	products = other.products;
	other.products = nullptr;
}

void Order::resize()
{
	productsCapacity = 2 * (productsCapacity + 1);
	MyString* buff = new MyString[productsCapacity];
	for (int i = 0; i < productsCount; i++)
		buff[i] = std::move(products[i]);

	delete[] products;
	products = buff;
}

Order::Order()
{
	name = "";
	productsCapacity = 16;
	productsCount = 0;
	products = new MyString[productsCapacity];
}

Order::Order(const Order& other)
{
	copyFrom(other);
}

Order::Order(Order&& other)
{
	moveFrom(std::move(other));
}

Order& Order::operator=(const Order& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Order& Order::operator=(Order&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Order::~Order()
{
	free();
}

void Order::addProduct(const MyString& prod)
{
	while (productsCapacity <= productsCount)
		resize();

	products[productsCount++] = prod;
}

void Order::addProduct(MyString&& prod)
{
	while (productsCapacity <= productsCount)
		resize();

	products[productsCount++] = std::move(prod);
}

size_t Order::orderTime() const
{
	size_t len = 0;
	for (int i = 0; i < productsCount; ++i)
		len += products[i].getSize();

	return len + productsCount;
}

const MyString* Order::getProducts() const
{
	return products;
}

const MyString& Order::getName() const
{
	return name;
}

unsigned Order::getCount() const
{
	return productsCount;
}
