#include "Spell.hpp"
#pragma warning (disable : 4996)

Spell::Spell() : name("identity"), effect([](Potion& p)->Potion& {return p; })
{}

Spell::Spell(const char* name, const std::function<Target& (Target&)>& effect)
{
    setName(name);
    setEffect(effect);
}

const char* Spell::getName() const
{
    return name;
}

void Spell::setName(const char* name)
{
    if (!name || strlen(name) > 20) {
        strcpy(this->name, "null");
        return;
    }
    strcpy(this->name, name);
}

Potion& Spell::apply(Potion& potion) const
{
    return effect(potion);
}

void Spell::setEffect(const std::function<Target& (Target&)>& effect)
{
    // Отново подаваме this и effect по копие, както споменахме в Potion
    // Освен това подаваме указател към функцията Potion::getEffect 
    // (обърнете внимание как се извиква статичен метод на клас)
    // Нужно е, защото ламбдата не е метод на Skill, поради което не можем
    // да достъпваме private членовете на Potion, въпреки че Skill e означен като friend.
    
    this->effect = [this, getEffect = Potion::getEffect, effect](Potion& potion)->Potion&
        {
            std::function<Target&(Target&)>& oldEffect = getEffect(potion);
            getEffect(potion) = [oldEffect, effect](Target& t) -> Target& 
                { 
                    return effect(oldEffect(t));
                };
            return potion;
        };
}

Spell Spell::operator+(const Spell& other) const
{
    Spell result;
    result.setName(name);
    result.effect = [this, other](Potion& x) -> Potion& { return apply(other.apply(x)); };
    return result;
}
