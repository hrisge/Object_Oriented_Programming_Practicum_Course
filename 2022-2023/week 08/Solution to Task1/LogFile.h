#pragma once
#include <iostream>
#include <fstream>
#include "TimeStamp.h"

const unsigned MAX_SIZE = 100;

class LogFile
{
	TimeStamp data[MAX_SIZE];
	unsigned size;

	void readFile(std::ifstream&, TimeStamp&);

public:
	LogFile();
	LogFile(std::ifstream&);

	int getLoginsAfterTime(unsigned, unsigned, unsigned) const;
	int loginsBetweenHours(unsigned, unsigned, unsigned, unsigned, unsigned, unsigned) const;
	int getLongestActivePeriod() const;
	bool isLoggedIn(unsigned) const;

};

