#include <iostream>

enum Major {
	COMPUTER_SCIENCE,
	SOFTWARE_ENGINEERING,
	MATHEMATICS,
	APPLIED_MATHEMATICS,
	_SIZE
};

struct Student {
	char firstName[17];
	char lastName[17];
	char fn[6];
	double average;
	Major major;
	
};

void printMajor(Major m) {
	switch (m) {
		case COMPUTER_SCIENCE: std::cout << "Computer Science"; break;
		case SOFTWARE_ENGINEERING: std::cout << "Software Engineering"; break;
		case MATHEMATICS: std::cout << "Mathematics"; break;
		case APPLIED_MATHEMATICS: std::cout << "Applied Mathematics"; break;
		default: std::cout << "invalid major"; break;
	}
}

void print(const Student& student) {
	std::cout << "First Name: " << student.firstName << std::endl;
	std::cout << "Last Name: " << student.lastName << std::endl;
	std::cout << "Faculty Number: " << student.fn << std::endl;
	std::cout << "Grade Average: " << student.average << std::endl;
	std::cout << "Major: ";
	printMajor(student.major);
	std::cout << std::endl;
}

void strncopy(const char* src, char* dest, size_t n) {
	int i = 0;
	for (i = 0; src[i] != '\0' && i < n; i++){
		dest[i] = src[i];
	}
	dest[i] = '\0';
}

size_t strlen(const char* str) {
	size_t i;
	for(i = 0; str[i]!='\0'; i++){}
	return i;
}

Student initStudent(const char* firstName, const char* lastName, const char* fn, double average, Major major) {
	Student s;
	strncopy(firstName, s.firstName, 16);
	strncopy(lastName, s.lastName, 16);
	strncopy(fn, s.fn, 5);
	s.average = average;
	s.major = major;
	return s;
}

int readMajor() {
	int major;
	std::cout << "Select Major: " << std::endl;
	for (int i = 0; i < Major::_SIZE; i++) {
		std::cout << i + 1 << ") ";
		printMajor((Major)i);
		std::cout << std::endl;
	}
	std::cin >> major;
	return major-1;

}

bool validFacultyNumber(const char* fn) {
	size_t length = strlen(fn);
	if (length != 5) return false;
	for (size_t i = 0; i < length; i++) {
		if (fn[i] < '0' || fn[i] > '9') return false;
	}
	return true;
}

Student readStudent() {
	char buf[1024];

	char firstName[17];
	std::cout << "First Name: ";
	std::cin.getline(buf, 1024);
	strncopy(buf, firstName, 16);

	char lastName[17];
	std::cout << "Last Name: ";
	std::cin.getline(buf,1024);
	strncopy(buf, lastName, 16);

	char fn[6];
	std::cout << "Faculty Number: ";
	std::cin.getline(buf, 1024);
	strncopy(buf, fn, 5);

	while (!validFacultyNumber(fn)) {
		std::cout << "Invalid Faculty Number" << std::endl;
		std::cout << "Faculty Number: ";
		std::cin.getline(buf, 1024);
		strncopy(buf, fn, 5);
	}

	double average;
	std::cout << "Grade Average: ";
	std::cin >> average;
	while (average < 2 || average > 6) {
		std::cout << "Invalid grade average" << std::endl;
		std::cout << "Grade Average: ";
		std::cin >> average;
	}
	
	int major = readMajor();
	while (major >= Major::_SIZE || major < 0) {
		std::cout << "Invalid Major" << std::endl;
		major = readMajor();
	}
	
	return initStudent(firstName, lastName, fn, average, (Major)major);
}
