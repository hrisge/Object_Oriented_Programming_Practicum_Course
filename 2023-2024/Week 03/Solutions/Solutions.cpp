#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#pragma warning (disable: 4996)

namespace Constants
{
	const constexpr unsigned MAX_SIZE = 100;
	const constexpr unsigned MAX_INT_LEN = 20;
	const constexpr unsigned MAX_NAME_SIZE = 17;
	const constexpr unsigned MAX_GROUP_SIZE = 1024;
    const constexpr unsigned MAX_CLIENT_NAME_SIZE = 51;
    const constexpr unsigned MAX_CLIENT_PHONE_SIZE = 21;
    const constexpr unsigned MAX_CLIENT_ADDRESS_SIZE = 101;
}

namespace MatrixMultiplication
{
	struct Matrix
	{
		unsigned matrix[Constants::MAX_SIZE][Constants::MAX_SIZE];
		unsigned rows;
		unsigned colls;
	};

	unsigned charToDigit(char ch)
	{
		return ch - '0';
	}
	unsigned convertStrToUnsigned(const char* str)
	{
		int res = 0;
		while (*str)
		{
			res = ((res * 10) + charToDigit(*str));
			str++;
		}
		return res;
	}
	size_t getFileLength(std::ifstream& ifs)
	{
		size_t currPos = ifs.tellg(), res = 0;
		ifs.seekg(0, std::ios::end);
		res = ifs.tellg();
		ifs.seekg(currPos, std::ios::beg);
		return res;
	}
	unsigned getCharCountFromFile(std::ifstream& ifs, char ch)
	{
		size_t currentPosition = ifs.tellg();
		ifs.seekg(0, std::ios::beg);

		if (!ifs.is_open())
			return 0;

		unsigned int count = 0;

		while (true)
		{
			char current = ifs.get();
			if (ifs.eof())
				break;

			if (current == ch)
				count++;
		}

		ifs.clear();
		ifs.seekg(currentPosition);
		return count;
	}

	Matrix loadMatrix(const char* fileName)
	{
		std::ifstream file(fileName);
		if (!file.is_open())
			throw std::runtime_error("File could not be open!");

		Matrix matrix;
		matrix.rows = getCharCountFromFile(file, '|') + 1;
		matrix.colls = getCharCountFromFile(file, ',') / matrix.rows + 1;

		file.seekg(0, std::ios::beg);
		char buff[Constants::MAX_INT_LEN];

		for (int i = 0; i < matrix.rows - 1; i++)
		{
			for (int j = 0; j < matrix.colls - 1; j++)
			{
				file.getline(buff, Constants::MAX_INT_LEN, ',');
				matrix.matrix[i][j] = convertStrToUnsigned(buff);
			}
			file.getline(buff, Constants::MAX_INT_LEN, '|');
			matrix.matrix[i][matrix.colls - 1] = convertStrToUnsigned(buff);
		}

		for (int j = 0; j < matrix.colls - 1; j++)
		{
			file.getline(buff, Constants::MAX_INT_LEN, ',');
			matrix.matrix[matrix.rows - 1][j] = convertStrToUnsigned(buff);
		}
		file.getline(buff, Constants::MAX_INT_LEN);
		matrix.matrix[matrix.rows - 1][matrix.colls - 1] = convertStrToUnsigned(buff);

		file.close();
		return matrix;
	}
	Matrix matrixMultiplication(const Matrix& matrix1, const Matrix& matrix2)
	{
		Matrix result;
		result.rows = matrix1.rows;
		result.colls = matrix2.colls;

		for (int i = 0; i < result.rows; i++)
		{
			for (int j = 0; j < result.colls; j++)
			{
				result.matrix[i][j] = 0;

				for (int k = 0; k < matrix2.rows; k++) {
					result.matrix[i][j] += matrix1.matrix[i][k] * matrix2.matrix[k][j];
				}
			}
		}

		return result;
	}
	Matrix matrixMultiplicationFromFile(const char* file1, const char* file2)
	{
		Matrix matrix1 = loadMatrix(file1);
		Matrix matrix2 = loadMatrix(file2);

		Matrix result = matrixMultiplication(matrix1, matrix2);
		return result;
	}
	Matrix matrixMultiplicationFromFile(const char* file1, const char* file2, const char* fileToSave)
	{
		Matrix res = matrixMultiplicationFromFile(file1, file2);

		std::ofstream saveFile(fileToSave, std::ios::trunc);
		if (!saveFile.is_open())
			throw std::runtime_error("Could not open file!");

		for (int i = 0; i < res.rows-1; i++)
		{
			for (int j = 0; j < res.colls-1; j++)
			{
				saveFile << std::to_string(res.matrix[i][j])<<',';
			}
			saveFile << std::to_string(res.matrix[i][res.colls-1]) << '|';
		}
		for (int j = 0; j < res.colls - 1; j++)
		{
			saveFile << std::to_string(res.matrix[res.rows - 1][j]) << ',';
		}
		saveFile << std::to_string(res.matrix[res.rows - 1][res.colls - 1]) << std::endl;

		saveFile.close();
		return res;
	}


}

namespace Student
{
	enum class HairColour
	{
		Brown,
		Black,
		Blonde,
		Red,
		White
	};

	struct Student
	{
		double averageGrade;
		char firstName[Constants::MAX_NAME_SIZE];
		char lastName[Constants::MAX_NAME_SIZE];
		unsigned fn;
		HairColour hair;
	};

	struct Group
	{
		Student students[Constants::MAX_GROUP_SIZE];
		unsigned groupSize;
	};

	HairColour getHairColourFromArray(const char* hair)
	{
		if (!strcmp(hair, "Brown"))
			return HairColour::Brown;
		else if (!strcmp(hair, "Black"))
			return HairColour::Black;
		else if (!strcmp(hair, "Blonde"))
			return HairColour::Blonde;
		else if (!strcmp(hair, "Red"))
			return HairColour::Red;
		else
			return HairColour::White;
	}
	char* getHairColourAsArray(const HairColour& colour)
	{
		char* toReturn = new char[Constants::MAX_NAME_SIZE];
		switch (colour)
		{
		case HairColour::Brown: strcpy(toReturn, "Brown"); break;
		case HairColour::Black: strcpy(toReturn, "Black"); break;
		case HairColour::Blonde: strcpy(toReturn, "Blonde"); break;
		case HairColour::Red: strcpy(toReturn, "Red"); break;
		case HairColour::White: strcpy(toReturn, "White"); break;
		}
		return toReturn;
	}
	void writeStudentToFile(std::ofstream& ofs, const Student& student)
	{
		ofs << student.firstName << ',' << student.lastName << ','<<student.fn<<','<<student.averageGrade<<',';
		char* hair = getHairColourAsArray(student.hair);
		ofs << hair << '\n';
		delete[] hair;
	}
	void writeGroupToFile(const char* fileName, const Group& group)
	{
		std::ofstream ofs(fileName, std::ios::trunc);
		if (!ofs.is_open())
			throw std::runtime_error("Could not open file!");

		for (int i = 0; i < group.groupSize; i++)
			writeStudentToFile(ofs, group.students[i]);

		ofs.close();
	}

	void loadStudentFromFile(std::ifstream& ifs, Student& student)
	{
		ifs.getline(student.firstName, Constants::MAX_NAME_SIZE, ',');
		ifs.getline(student.lastName, Constants::MAX_NAME_SIZE, ',');
		ifs >> student.fn;
		ifs.get();
		ifs >> student.averageGrade;
		ifs.get();
		char hairBuff[Constants::MAX_NAME_SIZE];
		ifs.getline(hairBuff, Constants::MAX_NAME_SIZE);
		student.hair = getHairColourFromArray(hairBuff);
	}
	void loadGroupFromFile(const char* fileName, Group& group)
	{
		std::ifstream ifs(fileName);
		if (!ifs.is_open())
			throw std::runtime_error("Could not open file!");

		group.groupSize = 0;
		while (!ifs.eof())
		{
			loadStudentFromFile(ifs, group.students[group.groupSize]);
			group.groupSize++;
		}

		ifs.close();
	}

}

namespace PizzaDelivery {

    enum class PizzaSize {
        S,
        M,
        L
    };

    enum class PizzaType {
        Margarita,
        Capricciosa,
        Kalzone,
        QuattroStagioni,
        QuattroFormaggi,
        Vegetariana,
        Marinara
    };

    struct Pizza {
        PizzaSize size;
        PizzaType type;
        double price;
    };

    struct PizzaOrder {
        char name[Constants::MAX_CLIENT_NAME_SIZE];
        char phone[Constants::MAX_CLIENT_PHONE_SIZE];
        char address[Constants::MAX_CLIENT_ADDRESS_SIZE];

        Pizza pizzas[Constants::MAX_GROUP_SIZE];
        unsigned orderSize;
    };

    struct PizzaOrderList {
        PizzaOrder orders[Constants::MAX_GROUP_SIZE];
        unsigned orderSize;
    };

    Pizza readPizza(std::ifstream& ifs) {
        Pizza pizza;
        if (ifs.is_open()) {
            ifs.read((char*)&pizza, sizeof(Pizza));
        }

        return pizza;
    }

    Pizza readPizza(const char* fileName) {
        std::ifstream ifs(fileName, std::ios::binary);

        Pizza pizza = readPizza(ifs);
        ifs.close();
        return pizza;
    }

    void savePizza(std::ofstream& ofs, const Pizza& pizza) {
        if (ofs.is_open()) {
            ofs.write((const char*)&pizza, sizeof(Pizza));
        }
    }

    void savePizza(const char* fileName, const Pizza& pizza) {
        std::ofstream ofs(fileName, std::ios::binary);
        savePizza(ofs, pizza);
        ofs.close();
    }

    PizzaOrder readPizzaOrder(std::ifstream& ifs) {
        if (!ifs.is_open()) {
            return {};
        }

        PizzaOrder order;
        ifs.read((char*)&order.address, sizeof(order.address));
        ifs.read((char*)&order.name, sizeof(order.name));
        ifs.read((char*)&order.phone, sizeof(order.phone));
        ifs.read((char*)&order.orderSize, sizeof(order.orderSize));
        for (int i = 0; i < order.orderSize; i++) {
            order.pizzas[i] = readPizza(ifs);
        }

        return order;
    }

    PizzaOrder readPizzaOrder(const char* fileName) {
        std::ifstream ifs(fileName, std::ios::binary);
        PizzaOrder order = readPizzaOrder(ifs);
        ifs.close();
        return order;
    }

    void savePizzaOrder(std::ofstream& ofs, const PizzaOrder& order) {
        if (!ofs.is_open()) {
            return;
        }

        ofs.write((const char*)&order.address, sizeof(order.address));
        ofs.write((const char*)&order.name, sizeof(order.name));
        ofs.write((const char*)&order.phone, sizeof(order.phone));
        ofs.write((const char*)&order.orderSize, sizeof(order.orderSize));
        for (int i = 0; i < order.orderSize; i++) {
            savePizza(ofs, order.pizzas[i]);
        }
    }

    void savePizzaOrder(const char* fileName, const PizzaOrder& order) {
        std::ofstream ofs(fileName, std::ios::binary);
        savePizzaOrder(ofs, order);
        ofs.close();
    }

    PizzaOrderList readPizzaOrderList(std::ifstream& ifs) {
        if (!ifs.is_open()) {
            return {};
        }

        PizzaOrderList list;
        ifs.read((char*)&list.orderSize, sizeof(list.orderSize));
        for (int i = 0; i < list.orderSize; i++) {
            list.orders[i] = readPizzaOrder(ifs);
        }

        return list;
    }

    PizzaOrderList readPizzaOrderList(const char* fileName) {
        std::ifstream ifs(fileName, std::ios::binary);
        PizzaOrderList list = readPizzaOrderList(ifs);
        ifs.close();
        return list;
    }


    void savePizzaOrderList(std::ofstream& ofs, const PizzaOrderList& list) {
        if (!ofs.is_open()) {
            return;
        }

        ofs.write((const char*)&list.orderSize, sizeof(list.orderSize));
        for (int i = 0; i < list.orderSize; i++) {
            savePizzaOrder(ofs, list.orders[i]);
        }
    }

    void savePizzaOrderList(const char* fileName, const PizzaOrderList& list) {
        std::ofstream ofs(fileName, std::ios::binary);
        savePizzaOrderList(ofs, list);
        ofs.close();
    }

}

namespace JobOffers {

    struct JobOffer {
        char companyName[Constants::MAX_NAME_SIZE];
        unsigned teamSize;
        unsigned vacationDays;
        long long salary;
    };

    struct JobOfferList {
        JobOffer offers[Constants::MAX_GROUP_SIZE];
        unsigned offerSize;
    };

    JobOffer readJobOffer() {
        JobOffer offer;
        std::cin.getline(offer.companyName, Constants::MAX_NAME_SIZE);
        std::cin >> offer.teamSize;
        std::cin >> offer.vacationDays;
        std::cin >> offer.salary;
        std::cin.get();
        return offer;
    }

    JobOfferList readJobOfferList() {
        JobOfferList list;
        std::cin >> list.offerSize;
        std::cin.get();
        for (int i = 0; i < list.offerSize; i++) {
            list.offers[i] = readJobOffer();
        }
        return list;
    }

    JobOffer readJobOffer(std::ifstream& ifs) {
        JobOffer offer;
        if (ifs.is_open()) {
            ifs.read((char*)&offer, sizeof(JobOffer));
        }
        return offer;
    }

    JobOfferList readJobOfferList(std::ifstream& ifs) {
        if (!ifs.is_open()) {
            return {};
        }

        JobOfferList list;
        ifs.read((char*)&list.offerSize, sizeof(list.offerSize));
        for (int i = 0; i < list.offerSize; i++) {
            list.offers[i] = readJobOffer(ifs);
        }

        return list;
    }

    void saveJobOffer(std::ofstream& ofs, const JobOffer& offer) {
        if (!ofs.is_open()) {
            return;
        }

        ofs.write((const char*)&offer, sizeof(JobOffer));
    }

    void saveJobOfferList(std::ofstream& ofs, const JobOfferList& list) {
        if (!ofs.is_open()) {
            return;
        }

        ofs.write((const char*)&list.offerSize, sizeof(list.offerSize));
        for (int i = 0; i < list.offerSize; i++) {
            saveJobOffer(ofs, list.offers[i]);
        }
    }

    void saveJobOfferList(const char* fileName, const JobOfferList& list) {
        std::ofstream ofs(fileName, std::ios::binary | std::ios::ate);
        saveJobOfferList(ofs, list);
        ofs.close();
    }

    void printJobOffer(const JobOffer &offer) {
        std::cout << offer.companyName << " " << offer.teamSize << " " << offer.vacationDays << " " << offer.salary << std::endl;
    }

    void filterOffers(const char* filePath, long long minSalary) {
        std::ifstream ifs(filePath, std::ios::binary);
        if (!ifs.is_open()) {
            return;
        }

        JobOfferList list = readJobOfferList(ifs);
        ifs.close();

        for (int i = 0; i < list.offerSize; i++) {
            if (list.offers[i].salary >= minSalary) {
                printJobOffer(list.offers[i]);
            }
        }

    }

    bool existOffer(const char* filePath, const char* name) {
        std::ifstream ifs(filePath, std::ios::binary);
        if (!ifs.is_open()) {
            return false;
        }

        JobOfferList list = readJobOfferList(ifs);
        ifs.close();

        for (int i = 0; i < list.offerSize; i++) {
            if (strcmp(list.offers[i].companyName, name) == 0) {
                return true;
            }
        }

        return false;
    }

    bool existOffer(const JobOfferList& list, const char* name) {
        for (int i = 0; i < list.offerSize; i++) {
            if (strcmp(list.offers[i].companyName, name) == 0) {
                return true;
            }
        }

        return false;
    }

    bool isPerfectOffer(const JobOffer &offer, int maxCoworkers, int minVacancyDays, int minSalary) {
        return offer.teamSize <= maxCoworkers && offer.vacationDays >= minVacancyDays && offer.salary >= minSalary;
    }

    void perfectOffer(const char* filePath, int maxCoworkers, int minVacancyDays, int minSalary) {
        std::ifstream ifs(filePath, std::ios::binary);
        if (!ifs.is_open()) {
            return;
        }

        JobOfferList list = readJobOfferList(ifs);
        ifs.close();

        for (int i = 0; i < list.offerSize; i++) {
            if (isPerfectOffer(list.offers[i], maxCoworkers, minVacancyDays, minSalary)) {
                printJobOffer(list.offers[i]);
            }
        }

    }

    void addOrder(JobOfferList& list, const JobOffer& offer) {
        if (list.offerSize >= Constants::MAX_GROUP_SIZE) {
            return;
        }

        list.offers[list.offerSize++] = offer;
    }

    struct JobOfferSystem {
        JobOfferList offers;
    };

    void printAllJobOffers(const JobOfferSystem &system) {
        for (int i = 0; i < system.offers.offerSize; i++) {
            printJobOffer(system.offers.offers[i]);
        }
    }

    void printJobOffersWithHigherSalary(const JobOfferSystem &system, long long minSalary) {
        for (int i = 0; i < system.offers.offerSize; i++) {
            if (system.offers.offers[i].salary >= minSalary) {
                printJobOffer(system.offers.offers[i]);
            }
        }
    }

    void startSystem() {
        JobOfferSystem system;
        while (true) {
            char action;
            std::cin >> action;
            bool shouldBreak = false;
            JobOffer offer;

            char buffer[Constants::MAX_NAME_SIZE];

            switch (action) {
                case 'a':
                    offer = readJobOffer();
                    addOrder(system.offers, offer);
                    break;
                case 'i':
                    printAllJobOffers(system);
                    break;
                case 's':
                    std::cin.getline(buffer, Constants::MAX_NAME_SIZE);
                    if (existOffer(system.offers, buffer)) {
                        std::cout << "Offer exists!" << std::endl;
                    } else {
                        std::cout << "Offer does not exist!" << std::endl;
                    }
                    break;
                case 'f':
                    int minSalary;
                    std::cin >> minSalary;
                    printJobOffersWithHigherSalary(system, minSalary);
                case 'q':
                    shouldBreak = true;
                default:
                    break;
            }

            if (shouldBreak) {
                break;
            }
        }
    }

}

int main()
{

}