#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

struct Task
{
private:
	char* name;
	char* problem;
	unsigned points;

public:
	Task(const char* name, const char* problem, unsigned points)
	{
		setName(name);
		setProblem(problem);
		setPoints(points);
	}
	Task()
	{
		name = nullptr;
		problem = nullptr;
		points = 0;
	}
	~Task()
	{
		delete[] name;
		delete[] problem;
		points = 0;
	}

	const char* getName() const
	{
		return name;
	}
	const char* getProblem() const
	{
		return problem;
	}
	unsigned getPoints() const
	{
		return points;
	}

	void setName(const char* name)
	{
		if (this->name != nullptr)
			delete[] this->name;

		int len = strlen(name);
		this->name = new char[len + 1];
		strcpy(this->name, name);
	}
	void setProblem(const char* problem)
	{
		if (this->problem != nullptr)
			delete[] this->problem;

		int len = strlen(problem);
		this->problem = new char[len + 1];
		strcpy(this->problem, problem);
	}
	void setPoints(unsigned points)
	{
		this->points = points;
	}

	void writeToFile(std::ofstream& ofs)
	{
		if (!ofs.is_open())
			throw std::runtime_error("File could not open!");

		int nameLen = strlen(name);
		int problemLen = strlen(problem);

		ofs.write((const char*)&nameLen, sizeof(nameLen));
		ofs.write(name, nameLen + 1);
		ofs.write((const char*)&problemLen, sizeof(problemLen));
		ofs.write(problem, problemLen + 1);
		ofs.write((const char*)&points, sizeof(points));
	}
	void readFromFile(std::ifstream& ifs)
	{
		if (!ifs.is_open())
			throw std::runtime_error("File could not open!");

		int nameLen = 0;
		int problemLen = 0;
		ifs.read((char*)&nameLen, sizeof(nameLen));
		ifs.read(name, nameLen + 1);
		ifs.read((char*)&problemLen, sizeof(problemLen));
		ifs.read(problem, problemLen + 1);
		ifs.read((char*)&points, sizeof(points));
	}
};

struct Exam
{
private:
	Task* tasks;
	unsigned numberOfTasks;
	unsigned minPoints;

	void copyTask(unsigned pos, const Task& task)
	{
		tasks[pos].setName(task.getName());
		tasks[pos].setProblem(task.getProblem());
		tasks[pos].setPoints(task.getPoints());
	}
public:   
	Exam(const Task* tasks, unsigned numberOfTasks, unsigned minPoints)
	{
		this->numberOfTasks = numberOfTasks;
		this->minPoints = minPoints;

		tasks = new Task[this->numberOfTasks];
		for (int i = 0; i < this->numberOfTasks; i++)
			copyTask(i, tasks[i]);
	}
	~Exam()
	{
		delete[] tasks;
		numberOfTasks = 0;
		minPoints = 0;
	}

	void writeToFile(const char* fileName) const
	{
		std::ofstream ofs(fileName, std::ios::binary);
		if (!ofs.is_open())
			throw std::runtime_error("File could not open!");

		writeToFile(ofs);
		ofs.close();
	}
	void writeToFile(std::ofstream& ofs)
	{
		if (!ofs.is_open())
			throw std::runtime_error("File could not open!");

		ofs.write((const char*)&numberOfTasks, sizeof(numberOfTasks));
		for (int i = 0; i < numberOfTasks; i++)
			tasks[i].writeToFile(ofs);
		
		ofs.write((const char*)&minPoints, sizeof(minPoints));
	}

	void readFromFile(const char* fileName)
	{
		std::ifstream ifs(fileName, std::ios::binary);
		if(!ifs.is_open())
			throw std::runtime_error("File could not open!");

		readFromFile(ifs);
		ifs.close();
	}
	void readFromFile(std::ifstream& ifs)
	{
		if (!ifs.is_open())
			throw std::runtime_error("File could not open!");

		if (tasks != nullptr)
			delete[] tasks;
		numberOfTasks = 0;
		minPoints = 0;

		ifs.read((char*)&numberOfTasks, sizeof(numberOfTasks));
		for (int i = 0; i < numberOfTasks; i++)
			tasks[i].readFromFile(ifs);

		ifs.read((char*)&minPoints, sizeof(minPoints));
	}

	void changeMin(unsigned newMin)
	{
		minPoints = newMin;
	}
	unsigned getMax() const
	{
		if (numberOfTasks == 0 || tasks == nullptr)
			return 0;

		unsigned currMax = tasks[0].getPoints();
		for (unsigned i = 1; i < numberOfTasks; i++)
		{
			if (tasks[i].getPoints() > currMax)
				currMax = tasks[i].getPoints();
		}
		return currMax;
	}
};



int main()
{

}