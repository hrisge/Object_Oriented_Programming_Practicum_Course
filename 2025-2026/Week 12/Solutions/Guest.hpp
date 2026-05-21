#pragma once

#include "Player.hpp"
class Guest : public Player{
    unsigned timeLeft;
public:
    Guest(unsigned id);
    bool canLevelUp() const override;
};