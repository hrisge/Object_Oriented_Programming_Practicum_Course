#include <iostream>
#include <fstream>

const constexpr int BUFFER_LENGTH = 1024;

void writeDiff(std::ifstream& before, std::ifstream& after, std::ofstream& ofs) {
    if (!before.is_open() || !after.is_open() || !ofs.is_open()) {
        return;
    }

    char beforeBuffer[BUFFER_LENGTH];
    char afterBuffer[BUFFER_LENGTH];

    while (!before.eof() && !after.eof()) {
        before.getline(beforeBuffer, BUFFER_LENGTH);
        after.getline(afterBuffer, BUFFER_LENGTH);

        if (strcmp(beforeBuffer, afterBuffer) == 0) {
            ofs << beforeBuffer << '\n';
        }
        else {
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