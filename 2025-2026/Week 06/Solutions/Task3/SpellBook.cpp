#include "SpellBook.hpp"
#pragma warning (disable : 4996)

SpellBook::SpellBook() : name("empty"), m_size(0) {}

SpellBook::SpellBook(const char* name) : m_size(0)
{
    setName(name);
}

const char* SpellBook::getName() const
{
    return name;
}

void SpellBook::setName(const char* name)
{
    if (!name || strlen(name) > 50) {
        strcpy(this->name, "null");
        return;
    }
    strcpy(this->name, name);
}

size_t SpellBook::size() const
{
    return m_size;
}

void SpellBook::addSpell(const char* name, const std::function<Target& (Target&)>& effect)
{
    book[m_size] = Spell(name, effect);
    m_size++;
}

void SpellBook::addSpell(const Spell& spell)
{
    book[m_size] = spell;
    m_size++;
}

void SpellBook::removeSpell(const char* name)
{
    if (name == nullptr) return;
    for (size_t i = 0; i < m_size; i++) {
        if (strcmp(book[i].getName(), name) == 0) {
            std::swap(book[i], book[m_size - 1]);
            m_size--;
        }
    }
}

Spell& SpellBook::operator[](size_t ind)
{
    return book[ind];
}

const Spell& SpellBook::operator[](size_t ind) const
{
    return book[ind];
}
