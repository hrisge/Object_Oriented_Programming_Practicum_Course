#include "Delivery.hpp"
#pragma warning (disable : 4996)

Delivery::Delivery(const char* name, int deliveryTime) : deliveryTime(deliveryTime) {
	strncpy(this->name, name, std::min((size_t)101, strlen(name)+1));
}

Delivery::Delivery() : Delivery("", 0) {}

const char* Delivery::getName() const
{
	return this->name;
}

int Delivery::getDeliveryTime() const
{
	return deliveryTime;
}

bool Delivery::operator==(const Delivery& other) const
{
	return strcmp(this->name, other.name) == 0 && this->deliveryTime == other.deliveryTime;
}

