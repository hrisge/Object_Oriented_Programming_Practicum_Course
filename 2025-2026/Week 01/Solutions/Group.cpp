#include <iostream>

...Student.cpp...

const size_t MAX_STUDENTS = 1024;

struct Group {
	size_t size;
	double average;
	Student students[MAX_STUDENTS];
};

bool hasCapacity(const Group& group) {
	return group.size < MAX_STUDENTS;
}

void addStudent(Group& group, const Student& student) {
	if (hasCapacity(group)) {
		group.students[group.size] = student;
		double averageSum = group.average * group.size;
		group.size++;
		group.average = (averageSum + student.average) / group.size;
	}
	else std::cout << "capacity has been reached" << std::endl;
}

Group initGroup() {
	char input = 'y';
	Group g = { 0,0,{} };
	while (input != 'n' && hasCapacity(g)) {
		Student s = readStudent();
		addStudent(g, s);
		std::cout << "Do you want to continue(y/n)?" << std::endl;
		std::cin >> input;
		std::cin.ignore();
	}
	if (!hasCapacity(g)) {
		std::cout << "capacity has been reached" << std::endl;
	}
	return g;
}

unsigned scholarshipCount(const Group& g, double minAverage) {
	unsigned count = 0;
	for (size_t i = 0; i < g.size; i++) {
		if (g.students[i].average >= minAverage) count++;
	}
	return count;
}

int strcmp(const char* str1, const char* str2) {
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	if (len1 < len2) return -1;
	else if (len2 < len1) return 1;
	else {
		for (size_t i = 0; i < len1; i++) {
			if (str1[i] > str2[i]) return 1;
			if (str1[i] < str2[i]) return -1;
		}
		return 0;
	}
}

void shiftRightFromTo(Group& group, size_t start, size_t end) {
	for (size_t i = end; i > start; i--) {
		group.students[i] = group.students[i - 1];
	}
}

size_t findMinFnIndexFrom(const Group& group, size_t start) {
	size_t minInd = start;
	for (size_t i = start; i < group.size; i++) {
		if (strcmp(group.students[minInd].fn, group.students[i].fn) > 0) minInd = i;
	}
	return minInd;
}

//Selection Sort
//сложност по време - O(n^2)
//сложност по памет - О(1)
//стабилен
void sortByFn(Group& group) {
	for (size_t i = 0; i < group.size; i++) {
		size_t minInd = findMinFnIndexFrom(group, i);
		Student s = group.students[minInd];
		shiftRightFromTo(group, i, minInd);
		group.students[i] = s;
	}
}

size_t findMinGradeIndexFrom(const Group& group, size_t start) {
	size_t minInd = start;
	for (size_t i = start; i < group.size; i++) {
		if (group.students[minInd].average > group.students[i].average) minInd = i;
	}
	return minInd;
}

void sortByGrade(Group& group) {
	for (size_t i = 0; i < group.size; i++) {
		size_t minInd = findMinGradeIndexFrom(group, i);
		Student s = group.students[minInd];
		shiftRightFromTo(group, i, minInd);
		group.students[i] = s;
	}
}

//тъй като сортирането, което е написано(Selection Sort), е стабилно, факултетните номера при равни оценки ще останат сортирани
void sortGroup(Group& group) {
	sortByFn(group);
	sortByGrade(group);
}

Group filterByMajor(const Group& group, Major major) {
	Group result = { 0,0,{} };
	for (size_t i = 0; i < group.size; i++) {
		if (group.students[i].major == major) addStudent(result, group.students[i]);
	}
	return result;
}

void printGroup(const Group& group) {
	for (size_t i = 0; i < group.size; i++) {
		print(group.students[i]);
	}
}