#include <iostream>
#pragma warning(disable: 4996)

const constexpr unsigned NAME_LEN = 50;
const constexpr unsigned PRODUCTS_CAPACITY = 100;

class Product {
	double price;
	unsigned quantity;
	char name[NAME_LEN];

public:
	Product() {
		setPrice(0);
		setQuantity(0);
		setName("");
	}
	Product(const char* name, double price, unsigned quantity) {
		setName(name);
		setPrice(price);
		setQuantity(quantity);
	}

	void setPrice(double price) {
		this->price = price;
	}
	void setQuantity(unsigned quantity) {
		this->quantity = quantity;
	}
	void setName(const char* name) {
		if (!name || strlen(name) >= NAME_LEN)
			return;

		strcpy(this->name, name);
	}

	double getPrice() const {
		return price;
	}
	unsigned getQuantity() const {
		return quantity;
	}
	const char* getName() const {
		return name;
	}

	void print() const {
		std::cout << "Name: " << getName() << " Price: " << getPrice() <<
			" Quantity: " << getQuantity() << std::endl;
	}
};


class Store {
	Product  products[PRODUCTS_CAPACITY];
	unsigned size;

public:
	Store() {
		size = 0;
	}

	void addProduct(const Product& product) {
		if (size >= PRODUCTS_CAPACITY)
			return;

		products[size++] = product;
	}
	void sellProduct(const char* name) {
		bool found = 0;
		for (unsigned i = 0; i < size; ++i) {
			if (found && i == size - 1)
				break;
			else if (found) {
				products[i] = products[i + 1];
				continue;
			}

			if (!strcmp(products[i].getName(), name)) {
				if (products[i].getQuantity() > 0)
					products[i].setQuantity(products[i].getQuantity() - 1);
				else
					products[i] = products[i + 1];
			}
		}
		size--;
	}
	void restock(const char* name, unsigned quantity) {
		for (unsigned i = 0; i < size; ++i) {
			if (!strcmp(products[i].getName(), name)) {
				products[i].setQuantity(quantity);
				return;
			}
		}
	}

	void displayProducts() const {
		for (unsigned i = 0; i < size; ++i)
			products[i].print();
	}
	
	
};