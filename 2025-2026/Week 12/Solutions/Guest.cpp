#include "Guest.hpp"

Guest::Guest(unsigned id) : Player(id), timeLeft(8) {}
bool Guest::canLevelUp() const { return false; }
