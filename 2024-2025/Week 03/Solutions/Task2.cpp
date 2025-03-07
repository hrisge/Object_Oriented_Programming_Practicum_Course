#include <iostream>
#pragma warning(disable: 4996)

const constexpr unsigned NAME_LEN = 50;
const constexpr unsigned DESCRIPTION_LEN = 1000;
const constexpr unsigned TASKS_SIZE = 10;

class Task {
	int points;
	char name[NAME_LEN];
	char description[DESCRIPTION_LEN];

public:
	Task() {
		setPoints(0);
		setName("");
		setDescription("");
	}
	Task(const char* name, const char* desription, int points) {
		setName(name);
		setDescription(desription);
		setPoints(points);
	}

	int getPoints() const {
		return points;
	}
	const char* getName() const {
		return name;
	}
	const char* getDescription() const {
		return description;
	}

	void setDescription(const char* description) {
		if (!description)
			return;

		std::strcpy(this->description, description);
	}
	void setName(const char* name) {
		if (!name)
			return;

		std::strcpy(this->name, name);
	}
	void setPoints(int points) {
		this->points = points;
	}
};

class Exam {
	Task tasks[TASKS_SIZE];
	int size = 0;
	int minPoints;

public:
	void addTask(const Task& task) {
		if (size >= TASKS_SIZE)
			return;

		tasks[size++] = task;
	}
	
	void changeMin(int minPoints) {
		this->minPoints = minPoints;
	}
	void getMax() {
		int max = 0;
		
		for (int i = 0; i < size; ++i)
			max += tasks[i].getPoints();
	}
};