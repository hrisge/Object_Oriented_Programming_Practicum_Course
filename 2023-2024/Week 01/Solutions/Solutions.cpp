#include <iostream>

const constexpr int NAME_LEN = 17;
const constexpr int MAX_LEN = 1024;

unsigned myStrlen(const char* str)
{
	if (!str)
		return 0;

	unsigned result = 0;
	while (*str)
	{
		result++;
		str++;
	}
	return result;
}
void myStrcpy(const char* source, char* dest)
{
	if (!source || !dest)
		return;
	while (*source)
	{
		*dest = *source;
		dest++;
		source++;
	}
	*dest = '\0';
}
int myStrcmp(const char* first, const char* second)
{
	if (!first || !second)
		return INT16_MIN; 

	while ((*first) && (*second) && ((*first) == (*second)))
	{
		first++;
		second++;
	}

	return (*first - *second);

}

enum class Specialty
{
	Informatics = 0,
	InformaticSystems,
	ComputerScience,
	SoftwareEngineering,
	DataAnalisys,
	Mathematics,
	Statistics,
	Error
};

struct Student
{
	char name[NAME_LEN];
	char lastName[NAME_LEN];
	unsigned fn;
	double averagGrades;
	Specialty spec;
};

void printSpecialty(const Specialty& spec)
{
	switch (spec)
	{
	case Specialty::Informatics: std::cout << "Informatics"; break;
	case Specialty::InformaticSystems: std::cout << "Informatic Systems"; break;
	case Specialty::ComputerScience: std::cout << "Computer Science"; break;
	case Specialty::SoftwareEngineering: std::cout << "Software Engineering"; break;
	case Specialty::DataAnalisys: std::cout << "Data Analisys"; break;
	case Specialty::Mathematics: std::cout << "Mathematics"; break;
	case Specialty::Statistics: std::cout << "Statistics"; break;
	case Specialty::Error: std::cout << "Error"; break;
	}
}
Specialty getSpecialtyFromConsole()
{
	char specialty[MAX_LEN];
	std::cin.clear();
	std::cin.getline(specialty, MAX_LEN);

	if (myStrcmp(specialty, "Informatics"))
		return Specialty::Informatics;
	else if (myStrcmp(specialty, "Informatic Systems"))
		return Specialty::InformaticSystems;
	else if (myStrcmp(specialty, "Computer Science"))
		return Specialty::ComputerScience;
	else if (myStrcmp(specialty, "Software Engineering"))
		return Specialty::SoftwareEngineering;
	else if (myStrcmp(specialty, "Data Analisys"))
		return Specialty::Mathematics;
	else if (myStrcmp(specialty, "Mathematics"))
		return Specialty::Mathematics;
	else if (myStrcmp(specialty, "Statistics"))
		return Specialty::Statistics;
	else
		return Specialty::Error;

}
void printStudent(const Student& st)
{
	std::cout << "Name: "<< st.name<<"\nLast Name: "<<st.lastName<<"\nFaculty Number: "<<st.fn<<"\nAverage Grades: "<<
		st.averagGrades<<"\nSpeciality: ";
	printSpecialty(st.spec);
	std::cout << std::endl;

}

Student initStudent(const char* name, const char* lastName, unsigned fn, double avGrade, Specialty spec)
{
	Student toReturn;
	if (name)
		myStrcpy(name, toReturn.name);

	if (lastName)
		myStrcpy(lastName, toReturn.lastName);

	if (fn >= 10000 && fn <= 99999)
		toReturn.fn = fn;
	else
		toReturn.fn = 0;

	if (avGrade >= 2 && avGrade <= 6)
		toReturn.averagGrades = avGrade;

	toReturn.spec = spec;
	return toReturn;
}

Student initStudentFromConsole()
{
	char name[NAME_LEN];
	char lastName[NAME_LEN];
	unsigned fn;
	double averagGrades;
	Specialty spec;

	std::cin.clear();
	std::cin.getline(name, NAME_LEN);
	std::cin.getline(lastName, NAME_LEN);
	std::cin >> fn;
	std::cin >> averagGrades;

	spec = getSpecialtyFromConsole();
	return initStudent(name, lastName, fn, averagGrades, spec);
}
int main()
{

}