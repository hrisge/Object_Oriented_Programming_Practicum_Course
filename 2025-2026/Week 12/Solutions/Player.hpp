#pragma once

#include <cmath>
class Player{
private:
    unsigned id;
    unsigned points;
    enum Stars{
        STAR1,
        STAR2,
        STAR3,
        STAR4,
        STAR5
    };
    Stars stars;
public:
    using Stars = Stars;
    Player(unsigned id);
    unsigned getId() const;
    unsigned getPoints() const;
    Stars getStars() const;
    virtual bool canLevelUp() const;
    virtual ~Player() = default;
};