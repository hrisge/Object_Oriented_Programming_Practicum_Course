#include "Potion.hpp"
#pragma warning (disable : 4996)

std::function<Target&(Target&)>& Potion::getEffect(Potion& potion)
{
    return potion.effect;
}

Potion::Potion() : name("identity"), effect([](Target& x)-> Target& {return x;}) {}

Potion::Potion(const char* name) : effect([](Target& x)-> Target& {return x; })
{
    setName(name);
}

Target& Potion::apply(Target& target) const
{
    return effect(target);
}

// правим композиция на двете функции
Potion Potion::operator+(const Potion& other) const
{
    Potion result;
    result.setName(name);
    // Важно е в ламбдата, да подаваме this и other по копие,
    // тъй като резултатният обект може да ги надживее
    // (ако са подадени по референция и някой от двата обекта бъде унищожен
    // преди result, то когато се опитаме да извикаме result.apply ще опита
    // да извика apply на изтрития обект)
    result.effect = [this, other](Target& x) ->Target& {return apply(other.apply(x)); };
    return result;
}

const char* Potion::getName() const
{
    return name;
}

void Potion::setName(const char* name)
{
    //не допускаме името да е nullptr
    if (!name || strlen(name) > 20) {
        strcpy(this->name, "null");
        return;
    }
    strcpy(this->name, name);
}
