#pragma once
#include "Target.hpp"
#include <functional>
//Forward Declaration
class Spell;

class Potion {
	char name[21];
	std::function<Target& (Target&)> effect;

	// Ключовата дума static означава, че тази функция не е свързана
	// с конкретен обект от този клас. Тя няма достъп до указателя
	// this, но има достъп до private полетата на обекти от тип Potion.
	// Този метод ще ползваме в класа Spell за да достъпваме ефекта на potion
	static std::function<Target& (Target&)>& getEffect(Potion& potion);

public:
	Potion();
	Potion(const char* name);
	Target& apply(Target& target) const;
	Potion operator+(const Potion& other) const;
	const char* getName() const;
	void setName(const char* name);

	// искаме Spell да е приятелски, за да може да достъпваме getEffect функцията
	friend Spell;
};