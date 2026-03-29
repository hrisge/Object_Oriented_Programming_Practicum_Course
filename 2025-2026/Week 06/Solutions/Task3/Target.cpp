#include "Target.hpp"

Target::Target() : health(100), weight(70), height(180), type(TargetType::HUMAN) {}

int Target::getHealth() const
{
    return health;
}

void Target::setHealth(int health)
{
    this->health = health;
}

int Target::getWeight() const
{
    return weight;
}

void Target::setWeight(int weight)
{
    this->weight = weight;
}

int Target::getHeight() const
{
    return height;
}

void Target::setHeight(int height)
{
    this->height = height;
}

TargetType Target::getType() const
{
    return type;
}

void Target::setType(TargetType type)
{
    if (type >= TargetType::HUMAN && type < TargetType::_SIZE) {
        this->type = type;
    }
}
