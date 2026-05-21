#include "PremiumUser.hpp"
#include "Player.hpp"

PremiumUser::PremiumUser(unsigned id, const std::string &username,
                         const std::string &password)
    : LoggedUser(id, password.c_str()), username(username) {}
bool PremiumUser::canLevelUp() const {
  return getStars() < Player::Stars::STAR5 && getPoints() >= pow(2, 7);
}
