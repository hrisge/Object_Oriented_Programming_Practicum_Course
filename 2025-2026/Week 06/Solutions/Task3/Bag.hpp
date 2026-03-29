#pragma once
#include <iostream>
#include "Potion.hpp"
#include "SpellBook.hpp"

class Bag {
	Potion* potions;
	SpellBook* spellBooks;
	size_t potionsSize;
	size_t potionsCapacity;
	size_t spellBooksSize;
	size_t spellBooksCapacity;
	void copy(const Bag& other);
	void free();
	template <class T>
	static void copyArr(size_t& capacity, size_t& size, T*& arr, size_t otherCapacity, size_t otherSize, const T* otherArr);
	template <class T>
	static void resize(size_t& capacity, size_t size, T*& arr);
	void resizePotions();
	void resizeBooks();
	Potion* findPotion(const char* name);
public:
	Bag();
	Bag(const Bag& other);
	Bag& operator=(const Bag& other);
	~Bag();

	void createBook(const char* name);
	SpellBook& getBook(size_t ind);
	const SpellBook& getBook(size_t ind) const;
	void createPotion(const char* name);
	Potion& getPotion(size_t ind);
	const Potion& getPotion(size_t ind) const;
	void printSpellBooks(std::ostream& out);
	void printPotions(std::ostream& out);
	Bag& applySpellsToAllPotions(const std::function<bool(const Spell&)>& p, const char* potionName);
	Bag& applyPotionsToTarget(const std::function<bool(const Potion&)>& p, Target& target);
	Bag& transferSpellsToNewBook(const std::function<bool(const Spell&)>& p, const char* bookName);
	Bag& sortPotionsBy(const std::function<bool(const Potion&, const Potion&)>& lessThan);
};


