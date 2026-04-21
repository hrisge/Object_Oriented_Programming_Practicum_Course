#include "Product.hpp"
#pragma warning (disable : 4996)

Product::Product() : Product("", {0,0,0}, 0, 0, Delivery(), _SIZE) {}

Product::Product(const char* name, const Size& size, double weight, double price, const Delivery& delivery, Category category) :
    size(size), weight(weight), price(price), delivery(delivery), category(category) {
    strncpy(this->name, name, std::min((size_t)101, strlen(name)+1));
}

const char* Product::getName() const
{
	return name;
}

const Size& Product::getSize() const
{
	return size;
}

double Product::getWeight() const
{
	return weight;
}

double Product::getPrice() const
{
	return price;
}

const Delivery& Product::getDelivery() const
{
	return delivery;
}

Category Product::getCategory() const
{
	return category;
}

bool Product::operator==(const Product& other) const {
	return strcmp(this->name, other.name) == 0 &&
		this->category == other.category &&
		this->delivery == other.delivery &&
		this->price == other.price &&
		this->size == other.size &&
		this->weight == other.weight;
}
