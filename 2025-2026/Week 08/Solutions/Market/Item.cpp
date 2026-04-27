#include "Item.hpp"

Item::Item() : product(nullptr), count(0) {}

Item::Item(Product* product, size_t count) : product(product), count(count) {
	if (!product) throw std::invalid_argument("Invalid product");
}

const Product& Item::getProduct() const { return *product; }

size_t Item::getCount() const { return count; }
