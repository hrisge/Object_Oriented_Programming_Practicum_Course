#include "Restaurant.h"

void Restaurant::addOrder(const Order& order)
{
	if (name != order.getName())
		throw ("Invalid name!");
	
	for (unsigned i = 0; i < order.getCount(); ++i)
	{
		bool containsAllProducts = false;
		for (unsigned j = 0; j < productsCount; ++j)
		{
			if (order.getProducts()[i] == products[j])
			{
				containsAllProducts = true;
				break;
			}
		}

		if (!containsAllProducts)
			throw ("Products not available!");
	}

	if (orderCount >= orderCapacity)
		resizeOrder();

	orders[orderCount++] = order;
}

void Restaurant::addOrder(Order&& order)
{
	if (name != order.getName())
		throw ("Invalid name!");

	for (unsigned i = 0; i < order.getCount(); ++i)
	{
		bool containsAllProducts = false;
		for (unsigned j = 0; j < productsCount; ++j)
		{
			if (order.getProducts()[i] == products[j])
			{
				containsAllProducts = true;
				break;
			}
		}

		if (!containsAllProducts)
			throw ("Products not available!");
	}

	orders[orderCount++] = (std::move(order));
}

void Restaurant::addProduct(const MyString& product)
{
	for (unsigned i = 0; i < productsCount; ++i)
	{
		if (product == products[i])
			return;
	}

	if (productsCapacity <= productsCount)
		resizeProducts();

	products[productsCount++] = product;
}

void Restaurant::addProduct(MyString&& product)
{
	for (unsigned i = 0; i < productsCount; ++i)
	{
		if (product == products[i])
			return;
	}

	if (productsCapacity <= productsCount)
		resizeProducts();

	products[productsCount++] = std::move(product);
}

const char* Restaurant::getName() const
{
	return name;
}

const MyString* Restaurant::getProducts() const
{
	return products;
}

const Order* Restaurant::getOrders() const
{
	return orders;
}

unsigned Restaurant::getProductsCapaciy() const
{
	return productsCapacity;
}

unsigned Restaurant::getProductsCount() const
{
	return productsCapacity;
}

unsigned Restaurant::getOrdersCapacity() const
{
	return orderCapacity;
}

unsigned Restaurant::getOrdersCount() const
{
	return orderCount;
}

void Restaurant::setName(const char* name)
{
	if (name == nullptr)
	{
		strcpy(this->name, "");
		return;
	}
	strcpy(this->name, name);
}

void Restaurant::setProducts(const MyString* products, unsigned productsCount)
{
	if (products == nullptr)
		throw std::invalid_argument("Invalid argument!");

	else if (this->products != nullptr)
		delete[] this->products;

	productsCapacity = productsCount;
	this->productsCount = productsCount;
	this->products = new MyString[productsCapacity];
	for (unsigned i = 0; i < productsCount; ++i)
		this->products[i] = products[i];
}

void Restaurant::setOrders(const Order* orders, unsigned ordersCount)
{
	if (orders == nullptr)
		throw std::invalid_argument("Invalid argument!");

	else if (this->orders != nullptr)
		delete[] this->orders;

	orderCapacity = ordersCount;
	this->orderCount = ordersCount;
	this->orders = new Order[orderCapacity];
	for (unsigned i = 0; i < orderCount; ++i)
		this->orders[i] = orders[i];
}

void Restaurant::setProducts(const MyString* products, unsigned productsCount, unsigned productsCapacity)
{	
	if (this->products != nullptr)
	{
		delete[] this->products;
		this->products = nullptr;
	}

	if (products == nullptr)
	{
		this->productsCount = 0;
		this->productsCapacity = productsCapacity;
		this->products = new MyString[productsCapacity];
		return;
	}

	this->productsCapacity = productsCount;
	this->productsCount = productsCount;
	this->products = new MyString[productsCapacity];
	for (unsigned i = 0; i < productsCount; ++i)
		this->products[i] = products[i];
}

void Restaurant::setOrders(const Order* orders, unsigned ordersCount, unsigned ordersCapacity)
{
	if (this->orders != nullptr)
	{
		delete[] this->orders;
		this->orders = nullptr;
	}

	if (orders == nullptr)
	{
		this->orderCount = 0;
		this->productsCapacity = productsCapacity;
		this->orders = new Order[productsCapacity];
		return;
	}

	this->orderCapacity = ordersCount;
	this->orderCount = ordersCount;
	this->orders = new Order[orderCapacity];
	for (unsigned i = 0; i < orderCount; ++i)
		this->orders[i] = orders[i];
}

void Restaurant::free()
{
	delete[] products;
	delete[] orders;
	productsCapacity = 0;
	productsCount = 0;
	orderCapacity = 0;
	orderCount = 0;
	strcpy(name, "");
}

void Restaurant::copyFrom(const Restaurant& other)
{
	strcpy(name, other.getName());
	setProducts(other.getProducts(), other.getProductsCount(), other.getProductsCapaciy());
	setOrders(other.getOrders(), other.getOrdersCount(), other.getOrdersCapacity());
}

void Restaurant::moveFrom(Restaurant&& other)
{
	strcpy(name, other.name);
	products = other.products;
	productsCapacity = other.productsCapacity;
	productsCount = other.productsCount;
	orders = other.orders;
	orderCount = other.orderCount;
	orderCapacity = other.orderCapacity;

	other.products = nullptr;
	other.orders = nullptr;
	other.productsCapacity = 0;
	other.productsCount = 0;
	other.orderCapacity = 0;
	other.orderCount = 0;
}

void Restaurant::resizeProducts()
{
	productsCapacity = 2 * (productsCapacity + 1);
	MyString* buff = new MyString[productsCapacity];
	for (unsigned i = 0; i < productsCount; ++i)
		buff[i] = products[i];

	delete[] products;
	products = buff;
}

void Restaurant::resizeOrder()
{
	orderCapacity = 2 * (orderCapacity + 1);
	Order* buff = new Order[orderCapacity];
	for (unsigned i = 0; i < orderCount; ++i)
		buff[i] = orders[i];

	delete[] orders;
	orders = buff;
}

Restaurant::Restaurant()
{
	setName("");
	setProducts(nullptr, 0, INITIAL_SIZE);
	setOrders(nullptr, 0, INITIAL_SIZE);
}

Restaurant::Restaurant(const Restaurant& other)
{
	copyFrom(other);
}

Restaurant::Restaurant(Restaurant&& other)
{
	moveFrom(std::move(other));
}

Restaurant& Restaurant::operator=(const Restaurant& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Restaurant& Restaurant::operator=(Restaurant&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Restaurant::~Restaurant()
{
	free();
}
