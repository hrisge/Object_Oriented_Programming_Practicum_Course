#include <iostream>
#include <fstream>

const constexpr int MAX_KEY_VALUE_LENGTH = 33;
const constexpr int BUFFER_LENGTH = 1024;

struct KeyValuePair {
    char key[MAX_KEY_VALUE_LENGTH];
    char value[MAX_KEY_VALUE_LENGTH];
};

int myStrCmp(const char* str1, const char* str2) {
    while (*str1 == *str2 && *str1 != '\0') {
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
        }
        else {
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