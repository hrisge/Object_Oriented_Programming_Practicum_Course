#include <iostream>
#include <fstream>

const size_t MAX_NAME_SIZE = 26;

struct Offer {
	char name[MAX_NAME_SIZE];
	unsigned coworkers;
	unsigned vacancyDays;
	uint64_t salary; //uint64_t e синоним за unsigned long long (целочислен тип без знак 64 бита / 8 байта)
};

void readOffer(Offer& offer) {
	std::cout << "Company Name: ";
	std::cin >> offer.name;
	std::cout << "Coworkers: ";
	std::cin >> offer.coworkers;
	std::cout << "Vacancy Days: ";
	std::cin >> offer.vacancyDays;
	std::cout << "Salary: ";
	std::cin >> offer.salary;
}

std::istream& readOffer(std::istream& in, Offer& offer) {
	in.read((char*)&offer, sizeof(Offer));
	return in;
}

void writeOffer(const Offer& offer) {
	std::cout << "Company Name: " << offer.name << std::endl;
	std::cout << "Coworkers: " << offer.coworkers << std::endl;
	std::cout << "Vacancy Days: " << offer.vacancyDays << std::endl;
	std::cout << "Salary: " << offer.salary << std::endl;
}

void writeOffer(std::ostream& out, const Offer& offer) {
	out.write((const char*)&offer, sizeof(Offer));
}

void writeOffer(const char* filePath, const Offer& offer) {
	std::ofstream out(filePath, std::ios::out | std::ios::app | std::ios::binary);
	if (!out.is_open()) {
		return;
	}
	writeOffer(out, offer);
	out.close();
}

void filterOffers(const char* filePath, uint16_t minSalary) {
	std::ifstream in(filePath, std::ios::in | std::ios::binary);
	if (!in.is_open()) {
		return;
	}
	Offer o;
	while (readOffer(in, o)) {
		if (o.salary >= minSalary) writeOffer(o);
	}
	in.close();
}

int strcmp(const char* str1, const char* str2) {
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	if (len1 < len2) return -1;
	else if (len2 < len1) return 1;
	else {
		for (size_t i = 0; i < len1; i++) {
			if (str1[i] > str2[i]) return 1;
			if (str1[i] < str2[i]) return -1;
		}
		return 0;
	}
}

bool existOffer(const char* filePath, const char* name) {
	std::ifstream in(filePath, std::ios::in | std::ios::binary);
	if (!in.is_open()) {
		return false;
	}
	Offer o;
	while (readOffer(in, o)) {
		if (strcmp(name, o.name) == 0) {
			in.close();
			return true;
		}
	}
	in.close();
	return false;
}

void perfectOffer(const char* filePath, const char* targetFilePath, unsigned maxCoworkers, unsigned minVacancyDays, uint64_t minSalary) {
	std::ifstream in(filePath, std::ios::in | std::ios::binary);
	std::ofstream out(targetFilePath, std::ios::out | std::ios::binary);
	if (!in.is_open() || !out.is_open()) {
		return;
	}
	Offer o;
	while (readOffer(in, o)) {
		if (o.salary >= minSalary && o.coworkers <= maxCoworkers && o.vacancyDays >= minVacancyDays) writeOffer(out, o);
	}
	in.close();
	out.close();
}

void addOffer(const char* filePath) {
	Offer o;
	readOffer(o);
	writeOffer(filePath, o);
}

void printAllOffers(const char* filePath) {
	Offer o;
	std::ifstream in(filePath, std::ios::in | std::ios::binary);
	while (readOffer(in, o)) {
		writeOffer(o);
	}
	in.close();
}

void checkExistsOffer(const char* filePath) {
	char name[MAX_NAME_SIZE];
	std::cin >> name;
	std::cout << std::boolalpha << existOffer(filePath, name) << std::endl;
}

void printFilteredOffers(const char* filePath) {
	unsigned minSalary;
	std::cin >> minSalary;
	filterOffers(filePath, minSalary);
}

void filterPerfectOffers(const char* filePath, const char* targetFilePath) {
	unsigned maxCoworkers;
	unsigned minVacationDays;
	uint64_t minSalary;
	std::cout << "Max Coworkers: ";
	std::cin >> maxCoworkers;
	std::cout << "Min Vacation Days: ";
	std::cin >> minVacationDays;
	std::cout << "Min Salary: ";
	std::cin >> minSalary;
	perfectOffer(filePath, targetFilePath, maxCoworkers, minVacationDays, minSalary);
}

//ще използваме perfect флага за да знаем, кога сме във файла със перфектните обяви
//правим го с цел да не могат да се добавят нови обяви към перфектните и да не може да се използва повече заявката за перфектни обяви
void runSystem(const char* filePath = "offers.bin", const char* perfectFilePath = "perfect.bin", bool perfect = false) {
	char input = 0;
	while (input != 'q') {
		std::cin >> input;
		switch (input) {
			case 'a': {
				if (!perfect) {
					addOffer(filePath);
				}
				else {
					std::cout << "Cannot add to perfect offers" << std::endl;
				}
				break;
			}
			case 'i': {
				printAllOffers(filePath);
				break;
			}
			case 's': {
				checkExistsOffer(filePath);
				break;
			}
			case 'f': {
				printFilteredOffers(filePath);
				break;
			}
			case 'p': {
				if (!perfect) {
					filterPerfectOffers(filePath, perfectFilePath);
					runSystem("perfect.bin", "perfect.bin", true);
				}
				else {
					std::cout << "Already in perfect offers" << std::endl;
				}
				break;
			}
			case 'q': break;
			default: {
				std::cout << "Invalid input" << std::endl;
			}
		}
	}
}

