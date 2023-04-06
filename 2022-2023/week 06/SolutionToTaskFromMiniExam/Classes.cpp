#include "Classes.h"

void Classes::free()
{
	delete[] students;
	capacity = 0;
	size = 0;
}

void Classes::copyFrom(const Classes& other)
{
	students = new Student[other.capacity];
	for (int i = 0; i < other.size; i++)
		students[i] = other.students[i];

	size = other.size;
	capacity = other.capacity;
}

Classes::Classes()
{
	students = nullptr;
	capacity = 0;
	size = 0;
}

Classes::Classes(const Classes& other)
{
	copyFrom(other);
}

Classes::~Classes()
{
	free();
}

Classes& Classes::operator=(const Classes& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

void Classes::saveClassesToFile(std::ofstream& ofs) const
{
	if (!ofs.is_open())
		return;

	ofs.write((const char*)&capacity, sizeof(int));
	ofs.write((const char*)&size, sizeof(int));

	for (int i = 0; i < size; i++)
	{
		students[i].saveStudentToFile(ofs);
	}
}

void Classes::readClassesFromFile(std::ifstream& ifs)
{
	if (!ifs.is_open())
		return;

	if (students != nullptr)
	{
		free();
	}

	ifs.read((char*)&capacity, sizeof(int));
	ifs.read((char*)&size, sizeof(int));

	students = new Student[capacity];
	for (int i = 0; i < size; i++)
		students[i].readStudentToFile(ifs);
}
