#include "Bag.hpp"

void Bag::copy(const Bag& other)
{
    copyArr(potionsCapacity, potionsSize, potions,
        other.potionsCapacity, other.potionsSize, other.potions);

    copyArr(spellBooksCapacity, spellBooksSize, spellBooks,
        other.spellBooksCapacity, other.spellBooksSize, other.spellBooks);
}

void Bag::free()
{
    delete[] potions;
    delete[] spellBooks;
}

//използваме шаблонна функция за да преизползваме код
template<class T>
void Bag::copyArr(size_t& capacity, size_t& size, T*& arr,
    size_t otherCapacity, size_t otherSize, const T* otherArr)
{
    size = otherSize;
    capacity = otherCapacity;
    arr = new T[capacity];
    for (size_t i = 0; i < size; i++) {
        arr[i] = otherArr[i];
    }
}


template<class T>
void Bag::resize(size_t& capacity, size_t size, T*& arr)
{
    if (capacity == 0) {
        capacity = 1;
    }
    capacity *= 2;
    T* newArr = new T[capacity];
    for (size_t i = 0; i < size; i++) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
}

void Bag::resizePotions()
{
    resize(potionsCapacity, potionsSize, potions);
}

void Bag::resizeBooks()
{
    resize(spellBooksCapacity, spellBooksSize, spellBooks);
}

Potion* Bag::findPotion(const char* name)
{
    for (size_t i = 0; i < potionsSize; i++) {
        if (strcmp(name, potions[i].getName()) == 0) return potions + i;
    }
    return nullptr;
}

Bag::Bag() : 
    potions(nullptr), spellBooks(nullptr), potionsCapacity(0), spellBooksCapacity(0),
    potionsSize(0), spellBooksSize(0) {}

Bag::Bag(const Bag& other)
{
    copy(other);
}

Bag& Bag::operator=(const Bag& other)
{
    if (this == &other) return *this;
    free();
    copy(other);
    return *this;
}

Bag::~Bag()
{
    free();
}

void Bag::createBook(const char* name)
{
    if (spellBooksSize >= spellBooksCapacity) {
        resizeBooks();
    }
    spellBooks[spellBooksSize++] = SpellBook(name);
}

SpellBook& Bag::getBook(size_t ind)
{
    return spellBooks[ind];
}

const SpellBook& Bag::getBook(size_t ind) const
{
    return spellBooks[ind];
}

void Bag::createPotion(const char* name) 
{
    if (potionsSize >= potionsCapacity) {
        resizePotions();
    }
    potions[potionsSize++] = Potion(name);
}

Potion& Bag::getPotion(size_t ind)
{
    return potions[ind];
}

const Potion& Bag::getPotion(size_t ind) const
{
    return potions[ind];
}

void Bag::printSpellBooks(std::ostream& out)
{
    for (size_t i = 0; i < spellBooksSize; i++) {
        out << spellBooks[i].getName() << ": " << std::endl;
        for (size_t j = 0; j < spellBooks[i].size(); j++) {
            out << " " << spellBooks[i][j].getName() << std::endl;
        }
    }
}

void Bag::printPotions(std::ostream& out)
{
    for (size_t i = 0; i < potionsSize; i++) {
        out << potions[i].getName() << std::endl;
    }
}

Bag& Bag::applySpellsToAllPotions(const std::function<bool(const Spell&)>& p, const char* potionName)
{
    Potion* potion = findPotion(potionName);
    if (!potion) return *this;
    for (size_t i = 0; i < spellBooksSize; i++) {
        for (size_t j = 0; j < spellBooks[i].size(); j++) {
            if (p(spellBooks[i][j])) spellBooks[i][j].apply(*potion);
        }
    }
    return *this;
}

Bag& Bag::applyPotionsToTarget(const std::function<bool(const Potion&)>& p, Target& target)
{
    for (size_t i = 0; i < potionsSize; i++) {
        if (p(potions[i])) potions[i].apply(target);
    }
    return *this;
}

Bag& Bag::transferSpellsToNewBook(const std::function<bool(const Spell&)>& p, const char* bookName)
{
    createBook(bookName);
    for (size_t i = 0; i < spellBooksSize-1; i++) {
        for (size_t j = 0; j < spellBooks[i].size(); j++) {
            if (p(spellBooks[i][j])) {
                spellBooks[spellBooksSize - 1].addSpell(spellBooks[i][j]);
                spellBooks[i].removeSpell(spellBooks[i][j].getName());
                j--; 
                // намаляме j, защото след като изтрием Spell, неговото място ще се 
                // запълни от друг, който не сме разгледали още
            }
        }
    }
    return *this;
}

Bag& Bag::sortPotionsBy(const std::function<bool(const Potion&, const Potion&)>& lessThan)
{
    for (size_t i = 0; i < potionsSize; i++) {
        for (size_t j = 0; j < potionsSize - i - 1; j++) {
            if (lessThan(potions[j + 1], potions[j])) std::swap(potions[j + 1], potions[j]);
        }
    }
    return *this;
}
