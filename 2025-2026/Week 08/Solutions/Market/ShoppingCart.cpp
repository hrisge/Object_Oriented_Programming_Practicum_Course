#include "ShoppingCart.hpp"
#pragma warning (disable : 4996)

Item& ShoppingCart::find(const std::function<bool(const Item&)>& f) {
	return products.find(f);
}

ShoppingCart::ShoppingCart(Array<Item> products, Market& market) 
	: products(products), market(&market) {}


ShoppingCart::ShoppingCart(const char* name, Market& market) : market(&market)  {
	setName(name);
}

const char* ShoppingCart::getName() const { return name; }

void ShoppingCart::setName(const char* name) {
	strncpy(this->name, name, std::min((size_t)101, strlen(name)+1));
}

double ShoppingCart::getPrice() const {
	double price = 0;
	for (const Item& item : products) {
		price += item.getProduct().getPrice() * item.getCount();
	}
	return price;
}

size_t ShoppingCart::getCount() const {
	size_t count = 0;
	for (const Item& item : products) {
		count += item.getCount();
	}
	return count;
}

int ShoppingCart::getDeliveryTime() const {
	return products.max<int>(
		[](const Item& item) {
			return item.getProduct().getDelivery().getDeliveryTime();
		}).getProduct().getDelivery().getDeliveryTime();
}

void ShoppingCart::addProduct(const Product& p) {
	Array<Item>::const_iterator toAdd =
		market->getItems().findPos([&](const Item& i) {return i.getProduct() == p; });
	if (toAdd) {
		Array<Item>::iterator existing =
			products.findPos([&](const Item& i) {return i.getProduct() == p; });
		if (existing) {
			(*existing).count++;
		}
		else {
			products.push_back(Item((*toAdd).product, 1));
		}
	}
	else {
		throw std::invalid_argument("Product is not listed in the market");
	}
}

void ShoppingCart::removeProduct(const Product& p) {
	products.remove_first([&](const Item& item) {return *item.product == p; });
}

void ShoppingCart::addCount(const Product& p, unsigned count) {
	find([&](const Item& item) {return *item.product == p; }).count += count;
}

void ShoppingCart::lowerCount(const Product& p, unsigned count) {
	
	Item& toLower = find([&](const Item& item) {return *item.product == p; });
	if (toLower.count < count) {
		throw std::invalid_argument("Cannot lower with that amount");
	}
	toLower.count -= count;
}

const Item& ShoppingCart::find(const std::function<bool(const Item&)>& f) const {
	return products.find(f);
}

const Item& ShoppingCart::findByName(const char* name) const {
	return find([&](const Item& item) {return strcmp(item.getProduct().getName(), name) == 0; });
}

const Item& ShoppingCart::maxByPrice() const {
	return products.max<double>([](const Item& item) {return item.getProduct().getPrice(); });
}

const Item& ShoppingCart::minByPrice() const {
	return products.min<double>([](const Item& item) {return item.getProduct().getPrice(); });
}

const Item& ShoppingCart::maxByDeliveryTime() const {
	return products.max<int>([](const Item& item)
		{ return item.getProduct().getDelivery().getDeliveryTime(); });
}

const Item& ShoppingCart::minByDeliveryTime() const {
	return products.min<int>([](const Item& item)
		{ return item.getProduct().getDelivery().getDeliveryTime(); });
}

void ShoppingCart::sortByPrice() {
	products = products.sortBy(
		[](const Item& l, const Item& r)
		{
			return l.getProduct().getPrice() < r.getProduct().getPrice();
		});
}

void ShoppingCart::sortByDeliveryTimeAscending() {
	products = products.sortBy(
		[](const Item& l, const Item& r)
		{
			return l.getProduct().getDelivery().getDeliveryTime() < r.getProduct().getDelivery().getDeliveryTime();
		});
}

void ShoppingCart::sortByDeliveryTimeDescending() {
	products = products.sortBy(
		[](const Item& l, const Item& r)
		{
			return l.getProduct().getDelivery().getDeliveryTime() > r.getProduct().getDelivery().getDeliveryTime();
		});
}

void ShoppingCart::sortByCount() {
	products = products.sortBy(
		[](const Item& l, const Item& r)
		{
			return l.getCount() < r.getCount();
		});
}

ShoppingCart ShoppingCart::filterByCategory(Category c) const {
	return 
		ShoppingCart(products.filter([&](const Item& item) {return item.getProduct().getCategory() == c; }), *market);
}

ShoppingCart ShoppingCart::filterByPriceRange(double begin, double end) const {
	return ShoppingCart(
		products.filter([&](const Item& item) {
			return item.getProduct().getPrice() >= begin && item.getProduct().getPrice() <= end;
		}), *market);
}

ShoppingCart ShoppingCart::filterByCountRange(size_t begin, size_t end) const {
	return ShoppingCart(
		products.filter([&](const Item& item) {
			return item.getCount() >= begin && item.getCount() <= end;
		}),
		*market);
}

ShoppingCart ShoppingCart::filterByDeliveryTimeRange(int begin, int end) const {
	return ShoppingCart(
		products.filter([&](const Item& item) {
			return item.getProduct().getDelivery().getDeliveryTime() >= begin &&
				item.getProduct().getDelivery().getDeliveryTime() <= end;
		}), *market);
}

void ShoppingCart::clear() {
	products = Array<Item>();
}

void ShoppingCart::confirmOrder()
{
	for (const Item& i : products) {
		market->sellProduct(i.getProduct(), i.getCount());
	}
}
