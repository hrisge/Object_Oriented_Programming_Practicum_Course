#include "LoggedUser.hpp"

LoggedUser::LoggedUser(unsigned id, const char* password) : Player(id) {
    if(strlen(password) > 8) throw std::runtime_error("password too long");
    strcpy(this->password, password);
}
bool LoggedUser::correctPassword(const std::string &password) {
    return strcmp(this->password, password.c_str()) == 0;
}
