#include "Student.h"
#pragma warning (disable: 4996)

void Student::free()
{
	delete[] name;
	name = nullptr;
	average = 0;
	fn = 1;
}

void Student::copyFrom(const Student& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);

	fn = other.fn;
	average = other.average;
}

Student::Student()
{
	average = 2;
	fn = 1;
	name = nullptr;
}

Student::Student(const Student& other)
{
	copyFrom(other);
}

Student& Student::operator=(const Student& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Student::~Student()
{
	free();
}

void Student::saveStudentToFile(std::ofstream& ofs) const
{
	if (!ofs.is_open())
		throw std::runtime_error("Not Open!");


	int len = strlen(name);
	ofs.write((const char*)&len, sizeof(len));
	ofs.write((const char*)name, len * sizeof(char));
	ofs.write((const char*)&fn, sizeof(unsigned));
	ofs.write((const char*)&average, sizeof(float));
}

void Student::readStudentToFile(std::ifstream& ifs)
{
	if (!ifs.is_open())
		return;

	int len = 0;
	ifs.read((char*)&len, sizeof(len));

	if (name != nullptr)
		free();

	name = new char[len + 1];
	ifs.read(name, len * sizeof(char));
	name[len] = '\0';

	ifs.read((char*)&fn, sizeof(unsigned));
	ifs.read((char*)&average, sizeof(float));
}
