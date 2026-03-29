#pragma once
#include "Potion.hpp"

class Spell {
	char name[21];
	std::function<Potion& (Potion&)> effect;
	void setEffect(const std::function<Target& (Target&)>& effect);
public:
	Spell();
	Spell(const char* name, const std::function<Target& (Target&)>& effect);
	const char* getName() const;
	void setName(const char* name);
	Potion& apply(Potion& potion) const;
	
	Spell operator+(const Spell& other) const;
};