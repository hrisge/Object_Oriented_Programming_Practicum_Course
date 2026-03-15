#include <iostream>
#include <fstream>

const char FILE_NAME[] = "result.txt";

void input(int& a, int& b, int& c) {
    std::cin >> a >> b >> c;
}

int getSum(int a, int b, int c) {
    return a + b + c;
}

int getMult(int a, int b, int c) {
    return a * b * c;
}

void writeToFile() {
    int a, b, c;
    input(a, b, c);

    int sum = getSum(a, b, c);
    int mult = getMult(a, b, c);

    std::ofstream ofs(FILE_NAME);
    if (!ofs.is_open()) {
        std::cout << "File could not open!" << std::endl;
        return;
    }
    ofs << sum << mult;

    ofs.close();
}

int readFromFileAndGetResult() {
    std::ifstream ifs(FILE_NAME);

    if (!ifs.is_open()) {
        std::cout << "File could not open!" << std::endl;
        return -1;
    }

    int sum, mult;
    ifs >> sum >> mult;

    std::cout << sum - mult;

    ifs.close();
}
