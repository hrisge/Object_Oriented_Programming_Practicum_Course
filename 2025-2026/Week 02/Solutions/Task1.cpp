#include <iostream>
#include <fstream>

int fileLenLinear(std::ifstream& ifs) {
	if (!ifs.is_open())
		return -1;
	
	int currPos = ifs.tellg();
	while (!ifs.eof())
		ifs.seekg(1, std::ios::cur);

	int res = ifs.tellg();

	ifs.seekg(currPos, std::ios::beg);
	return res;
}

int fileLenConst(std::ifstream& ifs) {
	if (!ifs.is_open())
		return -1;

	int currPos = ifs.tellg();
	ifs.seekg(0, std::ios::cur);

	int res = ifs.tellg();

	ifs.seekg(currPos, std::ios::beg);
	return res;
}
