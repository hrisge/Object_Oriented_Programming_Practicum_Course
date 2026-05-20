#pragma once

#include "Player.hpp"
#include <cstring>
#include <stdexcept>
class LoggedUser : public Player {
    char password[9];
public:
    LoggedUser(unsigned id, const char* password);
    bool correctPassword(const std::string &password);
};