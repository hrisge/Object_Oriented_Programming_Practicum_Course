#include "Player.hpp"

Player::Player(unsigned id) : id(id), points(0), stars(STAR1) {}
unsigned Player::getId() const { return id; }
unsigned Player::getPoints() const { return points; }
Player::Stars Player::getStars() const { return stars; }
bool Player::canLevelUp() const {
  if (stars < STAR5 && points >= pow(2, stars + 7)) {
    return true;
  }
  return false;
};
