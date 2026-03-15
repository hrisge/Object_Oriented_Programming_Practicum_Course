#include <iostream>
#include <fstream>


namespace StudentConstants {
    const int STR_SIZE = 17;
    const int FN_INIT_VAL = 0;
    const double GRADE_INIT_VAL = 0.0;
    const int FN_LENGTH = 5;
    const char FILE_NAME[] = "file.txt";

    namespace HairColorConstants {
        const char BLONDE[] = "blonde";
        const char BROWN[] = "brown";
        const char DARK[] = "dark";
        const char RED[] = "red";
        const char UNDEFINED[] = "undefined";
    }
}

namespace StudentUtil {
    int getNumLen(int num) {
        int len = 0;
        while (num) {
            len++;
            num /= 10;
        }
        return len;
    }
}

enum class HairColor {
    Blonde, Brown, Dark, Red, Undefined
};

struct Student {
    char firstName[StudentConstants::STR_SIZE] = "";
    char lastName[StudentConstants::STR_SIZE] = "";
    int fn = StudentConstants::FN_INIT_VAL;
    double averageGrade = StudentConstants::GRADE_INIT_VAL;
    HairColor hairColor = HairColor::Undefined;
};

const char* getFirstName(Student& student)  {
    return student.firstName;
}

const char* getLastName(Student& student)  {
    return student.lastName;
}

int getFn(Student& student)  {
    return student.fn;
}

double getAverageGrade(Student& student)  {
    return student.averageGrade;
}

const char* getHairColor(Student& student)  {
    switch (student.hairColor) {
    case HairColor::Blonde: return StudentConstants::HairColorConstants::BLONDE;
    case HairColor::Brown: return StudentConstants::HairColorConstants::BROWN;
    case HairColor::Dark: return StudentConstants::HairColorConstants::DARK;
    case HairColor::Red: return StudentConstants::HairColorConstants::RED;
    default: return StudentConstants::HairColorConstants::UNDEFINED;
    }
}

void setFirstName(Student& student, const char* firstName) {
    if (!isValidName(firstName)) {
        return;
    }
    std::strcpy(student.firstName, firstName);
}

void setLastName(const char* lastName) {
    if (!isValidName(lastName)) {
        return;
    }
    strcpy(this->lastName, lastName);
}

void Student::setFn(int fn) {
    if (!isValidFn(fn)) {
        return;
    }
    this->fn = fn;
}
void Student::setAverageGrade(double averageGrade) {
    this->averageGrade = averageGrade;
}

void Student::setHairColor(const char* hairColor) {
    if (!hairColor) {
        return;
    }
    if (strcmp(hairColor, StudentConstants::HairColorConstants::BLONDE) == 0) {
        this->hairColor = HairColor::Blonde;
    }
    else if (strcmp(hairColor, StudentConstants::HairColorConstants::BROWN) == 0) {
        this->hairColor = HairColor::Brown;
    }
    else if (strcmp(hairColor, StudentConstants::HairColorConstants::DARK) == 0) {
        this->hairColor = HairColor::Dark;
    }
    else if (strcmp(hairColor, StudentConstants::HairColorConstants::RED) == 0) {
        this->hairColor = HairColor::Red;
    }
    else {
        this->hairColor = HairColor::Undefined;
    }
}

void Student::setHairColor(HairColor hairColor) {
    this->hairColor = hairColor;
}

bool isValidName(const char* name) {
    if (!name || strlen(name) > StudentConstants::STR_SIZE) {
        return false;
    }
    return true;
}

bool isValidFn(int fn)  {
    if (StudentUtil::getNumLen(fn) != StudentConstants::FN_LENGTH) {
        return false;
    }
    return true;
}



Student Student(const char* firstName, const char* lastName, int fn, double averageGrade, HairColor HairColor) {
    setFirstName(firstName);
    setLastName(lastName);
    setFn(fn);
    setAverageGrade(averageGrade);
    setHairColor(hairColor);
}

Student::Student(const char* firstName, const char* lastName, int fn, double averageGrade, const char* hairColor) {
    setFirstName(firstName);
    setLastName(lastName);
    setFn(fn);
    setAverageGrade(averageGrade);
    setHairColor(hairColor);
}



void Student::save() {
    std::ofstream ofs(StudentConstants::FILE_NAME);
    if (!ofs.is_open()) {
        std::cout << "File could not open" << std::endl;
        return;
    }
    save(ofs);
    ofs.close();
}
void Student::save(const char* fileName) {
    std::ofstream ofs(fileName);
    if (!ofs.is_open()) {
        std::cout << "File could not open" << std::endl;
        return;
    }
    save(ofs);
    ofs.close();
}
void Student::save(std::ofstream& ofs) {
    if (!ofs.is_open()) {
        std::cout << "File could not open" << std::endl;
        return;
    }
    ofs << getFirstName() << "," << getLastName() << ",";
    ofs << getFn() << "," << getAverageGrade() << ",";
    ofs << getHairColor();
}

void Student::load() {
    std::ifstream ifs(StudentConstants::FILE_NAME);
    if (!ifs.is_open()) {
        std::cout << "File could not open" << std::endl;
        return;
    }
    load(ifs);
    ifs.close();
}
void Student::load(const char* fileName) {
    std::ifstream ifs(fileName);
    if (!ifs.is_open()) {
        std::cout << "File could not open" << std::endl;
        return;
    }
    load(ifs);
    ifs.close();
}
void Student::load(std::ifstream& ifs) {
    if (!ifs.is_open()) {
        std::cout << "File could not open" << std::endl;
        return;
    }

    char buffer[StudentConstants::STR_SIZE];
    int fn;
    double grade;

    ifs.getline(buffer, StudentConstants::STR_SIZE, ',');
    setFirstName(buffer);
    ifs.ignore();

    ifs.getline(buffer, StudentConstants::STR_SIZE, ',');
    setLastName(buffer);
    ifs.ignore();

    ifs >> fn;
    setFn(fn);

    ifs >> grade;
    setAverageGrade(grade);

    ifs.getline(buffer, StudentConstants::STR_SIZE);
    setHairColor(buffer);
}

void Student::print() const {
    std::cout << "First name: " << getFirstName() << std::endl;
    std::cout << "Last name: " << getLastName() << std::endl;
    std::cout << "Faculty number: " << getFn() << std::endl;
    std::cout << "Average grade: " << getAverageGrade() << std::endl;
    std::cout << "Hair color: " << getHairColor(); //////////////
    std::cout << std::endl;
}