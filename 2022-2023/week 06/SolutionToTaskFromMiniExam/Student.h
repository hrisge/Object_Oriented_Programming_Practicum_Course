#pragma once
#include <iostream>
#include <fstream>

class Student
{
	float average;
	unsigned fn;
	char* name;


	void free();
	void copyFrom(const Student&);

public:
	Student();
	Student(const Student&);
	Student& operator=(const Student&);
	~Student();

	void saveStudentToFile(std::ofstream&) const;
	void readStudentToFile(std::ifstream&);
};

