#pragma once
#include "Product.hpp"

class Market;
class ShoppingCart;

// Item държи указател към продукт, защото искаме да подсигурим, че веднъж добавен продукт
// в магазина ще живее до края на живота на магазина, и освен това, ще можем да подаваме
// същия продукт в колички(без да има нужда да го копираме)
class Item {
	Product* product;
	size_t count;

public:
	Item();
	Item(Product* product, size_t count);

	const Product& getProduct() const;
	size_t getCount() const;

	friend ShoppingCart;
	friend Market;
};