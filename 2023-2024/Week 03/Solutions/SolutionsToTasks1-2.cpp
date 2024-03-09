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
		ifs.seekg(0, currPos);
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



int main()
{

}