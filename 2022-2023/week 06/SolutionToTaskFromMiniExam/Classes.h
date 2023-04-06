#pragma once
#include "Student.h"
#include <fstream>

class Classes
{
	Student* students;
	int capacity;
	int size;


	void free();
	void copyFrom(const Classes&);

public:
	Classes();
	Classes(const Classes& other);
	~Classes();
	Classes& operator=(const Classes& other);

	void saveClassesToFile(std::ofstream& ofs) const;
	void readClassesFromFile(std::ifstream& ifs);

};

