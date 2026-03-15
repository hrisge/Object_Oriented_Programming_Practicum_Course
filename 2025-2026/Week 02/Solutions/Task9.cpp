#include <iostream>
#include <fstream>

const constexpr int MAX_USER_FIELD_LENGTH = 129;
const constexpr int MAX_USERS = 100;


struct User {
    char name[MAX_USER_FIELD_LENGTH];
    char username[MAX_USER_FIELD_LENGTH];
    char password[MAX_USER_FIELD_LENGTH];
};

void writeUserToFile(const User& user, std::ofstream& ofs) {
    if (!ofs.is_open()) {
        return;
    }

    ofs << user.name << ' ' << user.username << ' ' << user.password << std::endl;
}

void readUserFromFile(User& user, std::ifstream& ifs) {
    if (!ifs.is_open()) {
        return;
    }

    ifs >> user.name >> user.username >> user.password;
}


struct System {
    int size;
    User users[MAX_USERS];
};

void writeSystemToFile(const System& system, std::ofstream& ofs) {
    if (!ofs.is_open()) {
        return;
    }

    ofs << system.size << std::endl;
    for (int i = 0; i < system.size; ++i) {
        writeUserToFile(system.users[i], ofs);
    }
}

void readSystemFromFile(System& system, std::ifstream& ifs) {
    if (!ifs.is_open()) {
        return;
    }

    ifs >> system.size;
    for (int i = 0; i < system.size; ++i) {
        readUserFromFile(system.users[i], ifs);
    }
}