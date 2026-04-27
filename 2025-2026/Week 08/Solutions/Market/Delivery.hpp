#pragma once
#include <cstring>
#include <algorithm>

class Delivery {
	char name[101];
	int deliveryTime;
public:
	Delivery(const char* name, int deliveryTime);
	Delivery();

	const char* getName() const;
	int getDeliveryTime() const;

	bool operator==(const Delivery& other) const;
};