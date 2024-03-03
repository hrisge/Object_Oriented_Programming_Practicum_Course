#include <iostream>
#include <fstream>

const constexpr int MAX_KEY_VALUE_LENGTH = 33;
const constexpr int BUFFER_LENGTH = 1024;

struct KeyValuePair
{
    char key[MAX_KEY_VALUE_LENGTH];
    char value[MAX_KEY_VALUE_LENGTH];
};

int myStrCmp(const char* str1, const char* str2) {
    while(*str1 == *str2 && *str1 != '\0') {
        str1++;
        str2++;
    }

    return *str1 - *str2;
}

void replaceKeys(std::ifstream& ifs, std::ofstream& ofs, const KeyValuePair& pair) {

    if (!ifs.is_open() || !ofs.is_open()) {
        return;
    }

    char buffer[BUFFER_LENGTH];

    while (true) {
        ifs >> buffer;
        char delim = ifs.get();
        if (ifs.eof()) {
            break;
        }
        if (myStrCmp(buffer, pair.key) == 0) {
            ofs << pair.value;
        } else {
            ofs << buffer;
        }
        if (!ifs.eof()) {
            ofs << delim;
        }
    }
}

void replaceKeys(std::ifstream& ifs, std::ofstream& ofs, const KeyValuePair* pairArr, int pairArrSize) {

    if (!ifs.is_open() || !ofs.is_open()) {
        return;
    }

    char buffer[BUFFER_LENGTH];

    while (true) {
        ifs >> buffer;
        char delim = ifs.get();
        if (ifs.eof()) {
            break;
        }
        bool hasKey = false;
        for (int i = 0; i < pairArrSize; i++) {
            if (myStrCmp(buffer, pairArr[i].key) == 0) {
                ofs << pairArr[i].value;
                hasKey = true;
            }
        }
        if (!hasKey) {
            ofs << buffer;
        }
        if (!ifs.eof()) {
            ofs << delim;
        }
    }
}

const constexpr int MAX_RELATION_SIZE = 25;

struct Pair {
    int x;
    int y;
};

struct Relation {
    int size;
    Pair pairs[MAX_RELATION_SIZE];
};

void writePairToFile(std::ofstream& ofs, const Pair& pair) {
    if (!ofs.is_open()) {
        return;
    }
    ofs << pair.x << ' '<< pair.y << std::endl;
}

Pair readPairFromFile(std::ifstream & ifs) {
    Pair pair;
    if (!ifs.is_open()) {
        return pair;
    }

    ifs >> pair.x >> pair.y;
    return pair;
}

void writeRelationToFile(std::ofstream& ofs, const Relation& relation) {
    if (!ofs.is_open()) {
        return;
    }

    ofs << relation.size << std::endl;
    for (int i = 0; i <relation.size; ++i) {
        writePairToFile(ofs, relation.pairs[i]);
    }
}

Relation readRelationFromFile(std::ifstream& ifs) {
    Relation relation;

    ifs >> relation.size;
    for (int i = 0; i < relation.size; ++i) {
        relation.pairs[i] = readPairFromFile(ifs);
    }
    return relation;
}

const constexpr int MAX_USER_FIELD_LENGTH = 129;

struct User {
    char name[MAX_USER_FIELD_LENGTH];
    char username[MAX_USER_FIELD_LENGTH];
    char password[MAX_USER_FIELD_LENGTH];
};

void writeUserToFile(std::ofstream& ofs, const User& user) {
    if (!ofs.is_open()) {
        return;
    }

    ofs << user.name << ' ' << user.username << ' ' << user.password << std::endl;
}

User readUserFromFile(std::ifstream& ifs) {
    User user;
    if (!ifs.is_open()) {
        return user;
    }

    ifs >> user.name >> user.username >> user.password;
    return user;
}

const constexpr int MAX_USERS = 100;

struct System {
    int size;
    User users[MAX_USERS];
};

void writeSystemToFile(std::ofstream& ofs, const System& system) {
    if (!ofs.is_open()) {
        return;
    }

    ofs << system.size << std::endl;
    for (int i = 0; i < system.size; ++i) {
        writeUserToFile(ofs, system.users[i]);
    }
}

System readSystemFromFile(std::ifstream& ifs) {
    System system;
    if (!ifs.is_open()) {
        return system;
    }

    ifs >> system.size;
    for (int i = 0; i < system.size; ++i) {
        system.users[i] = readUserFromFile(ifs);
    }
    return system;
}

void writeDiff(std::ifstream& before, std::ifstream& after, std::ofstream& ofs) {
    if (!before.is_open() || !after.is_open() || !ofs.is_open()) {
        return;
    }

    char beforeBuffer[BUFFER_LENGTH];
    char afterBuffer[BUFFER_LENGTH];

    while (!before.eof() && !after.eof()) {
        before.getline(beforeBuffer, BUFFER_LENGTH);
        after.getline(afterBuffer, BUFFER_LENGTH);

        if (myStrCmp(beforeBuffer, afterBuffer) == 0) {
            ofs << beforeBuffer << '\n';
        } else {
            if (!before.eof()) {
                ofs << "- " << beforeBuffer << '\n';
            }
            if (!after.eof()) {
                ofs << "+ " << afterBuffer << '\n';
            }
        }
        ofs.flush();
    }

    while (true) {
        before.getline(beforeBuffer, BUFFER_LENGTH);
        if (before.eof()) {
            break;
        }
        ofs << "- " << beforeBuffer << '\n';
    }

    while (true) {
        after.getline(afterBuffer, BUFFER_LENGTH);
        if (after.eof()) {
            break;
        }
        ofs << "+ " << afterBuffer << '\n';
    }
}