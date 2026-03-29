#pragma once
#include "Spell.hpp"

class SpellBook {
	char name[51];
	Spell book[80];
	size_t m_size;
public:
	SpellBook();
	SpellBook(const char* name);
	const char* getName() const;
	void setName(const char* name);
	size_t size() const;
	void addSpell(const char* name, const std::function<Target&(Target&)>& effect);
	void addSpell(const Spell& spell);
	void removeSpell(const char* name);
	//константен и неконстантен operator[]
	Spell& operator[](size_t ind);
	const Spell& operator[](size_t ind) const;
};