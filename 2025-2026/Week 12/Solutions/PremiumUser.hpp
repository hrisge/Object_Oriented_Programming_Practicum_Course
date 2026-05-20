#pragma once

#include "LoggedUser.hpp"
#include <string>
class PremiumUser : public LoggedUser {
    std::string username;
public:
    PremiumUser(unsigned id, const std::string& username, const std::string& password);
    bool canLevelUp() const override;
};