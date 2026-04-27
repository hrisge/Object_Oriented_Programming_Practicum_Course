#include "User.hpp"
#pragma warning (disable : 4996)

User::User(const char* name, double money, Market& market) : money(money), market(market) {
	strncpy(this->name, name, std::min((size_t)100, strlen(name)));
}

void User::addCart(const char* name) {
	carts.push_back(new ShoppingCart(name, market));
}

void User::renameCart(ShoppingCart& cart, const char* newName) {
	cart.setName(newName);
}

ShoppingCart& User::find(const std::function<bool(const ShoppingCart&)>& f) {
	return *carts.find([&](ShoppingCart* const& s) {return f(*s); });
}

const ShoppingCart& User::find(const std::function<bool(const ShoppingCart&)>& f) const {
	return *carts.find([&](ShoppingCart* const& s) {return f(*s); });
}

// забележете, че времевата сложност на тази фунцкия ще е O(n * k), където k е дължината
// на най-дългата количка, защото за всяка итерация в цикъла на max се изпълнява
// getPrice, което е линейно спрямо дължината на количката, т. е. в най-лошият случай
// ще имаме n*k итерации
// същото важи и за sort (за тях е O(n * log(n) * k)) и filter функциите
ShoppingCart& User::maxByPrice() {
	return *carts.max<double>([](ShoppingCart* s) {return s->getPrice(); });
}

const ShoppingCart& User::maxByPrice() const {
	return *carts.max<double>([](ShoppingCart* s) {return s->getPrice(); });
}

ShoppingCart& User::minByPrice() {
	return *carts.min<double>([](ShoppingCart* s) {return s->getPrice(); });
}

const ShoppingCart& User::minByPrice() const {
	return *carts.min<double>([](ShoppingCart* s) {return s->getPrice(); });
}

ShoppingCart& User::maxByDeliveryTime() {
	return *carts.max<double>([](ShoppingCart* s) {return s->getDeliveryTime(); });
}

const ShoppingCart& User::maxByDeliveryTime() const {
	return *carts.max<double>([](ShoppingCart* s) {return s->getDeliveryTime(); });
}

ShoppingCart& User::minByDeliveryTime() {
	return *carts.min<double>([](ShoppingCart* s) {return s->getDeliveryTime(); });
}

const ShoppingCart& User::minByDeliveryTime() const {
	return *carts.min<double>([](ShoppingCart* s) {return s->getDeliveryTime(); });
}

ShoppingCart& User::maxByCount() {
	return *carts.max<double>([](ShoppingCart* s) {return s->getCount(); });
}

const ShoppingCart& User::maxByCount() const {
	return *carts.max<double>([](ShoppingCart* s) {return s->getCount(); });
}

ShoppingCart& User::minByCount() {
	return *carts.min<double>([](ShoppingCart* s) {return s->getCount(); });
}

const ShoppingCart& User::minByCount() const {
	return *carts.min<double>([](ShoppingCart* s) {return s->getCount(); });
}

User& User::sortByPrice() {
	carts = carts.sortBy<double>([](ShoppingCart* s) {return s->getPrice(); });
	return *this;
}

User& User::sortByDeliveryTimeAscending() {
	carts = carts.sortBy<double>([](ShoppingCart* s) {return s->getDeliveryTime(); });
	return *this;
}

User& User::sortByDeliveryTimeDescending() {
	carts = carts.sortBy<double>([](ShoppingCart* s) {return s->getDeliveryTime(); }).reverse();
	return *this;
}

User& User::sortByCount() {
	carts = carts.sortBy<double>([](ShoppingCart* s) {return s->getCount(); });
	return *this;
}

User& User::filterByPriceRange(double begin, double end) {
	carts = carts.filter([&](ShoppingCart* s) {
		return begin <= s->getPrice() && s->getPrice() <= end;
		});
	return *this;
}

User& User::filterByDeliveryTimeRange(int begin, int end) {
	carts = carts.filter([&](ShoppingCart* s) {
		return begin <= s->getDeliveryTime() && s->getDeliveryTime() <= end;
		});
	return *this;
}

User& User::filterByCountRange(size_t begin, size_t end) {
	carts = carts.filter([&](ShoppingCart* s) {
		return begin <= s->getCount() && s->getCount() <= end;
		});
	return *this;
}

User& User::addToAllCarts(const Product& product) {
	for (ShoppingCart* s : carts) {
		s->addProduct(product);
	}
	return *this;
}

// ако map-нем количките директно към продукти и след това извикаме max
/*
		carts.
		map<Product>([](ShoppingCart* const& s) {return s->maxByPrice().getProduct(); }).
		max<double>([](const Product& i) {return i.getPrice(); });
*/
// понеже map конструира нов масив, той ще се изтрие след края на израза,
// а max връща референция, т. е. ще получим висяща референция към продукт
// от изтрития масив
// 
// за това връщаме продукта от Item, за който сме сигурни, че ще живее до края на програмата
const Product& User::maxProductByPrice() const {
	return carts.
		map<Item>([](ShoppingCart* s) {return s->maxByPrice(); }).
		max<double>([](const Item& i) {return i.getProduct().getPrice(); })
		.getProduct();
}

const Product& User::minProductByPrice() const {
	return carts.
		map<Item>([](ShoppingCart* s) {return s->minByPrice(); }).
		min<double>([](const Item& i) {return i.getProduct().getPrice(); })
		.getProduct();
}

const Product& User::maxProductByDeliveryTime() const {
	return carts.
		map<Item>([](ShoppingCart* s) {return s->maxByDeliveryTime(); }).
		max<int>([](const Item& i) {return i.getProduct().getDelivery().getDeliveryTime(); })
		.getProduct();
}

const Product& User::minProductByDeliveryTime() const {
	return carts.
		map<Item>([](ShoppingCart* s) {return s->minByDeliveryTime(); }).
		min<int>([](const Item& i) {return i.getProduct().getDelivery().getDeliveryTime(); })
		.getProduct();
}
