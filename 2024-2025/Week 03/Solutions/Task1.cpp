#include <iostream>
#pragma warning(disable: 4996)

const constexpr unsigned NAME_LEN = 50;

class Teacher {
	unsigned age;
	unsigned experience;
	char name[NAME_LEN];

public:
	Teacher(){
		setAge(0);
		setExperience(0);
		setName("");
	}
	Teacher(unsigned age, unsigned experience, const char* name) {
		setAge(age);
		setExperience(experience);
		setName(name);
	}
	Teacher(const Teacher& other) {
		setAge(other.getAge());
		setExperience(other.getExperience());
		setName(other.getName());
	}


	void setAge(unsigned age) {
		if (age > 120)
			this->age = 0;
		else
			this->age = age;
	}
	void setExperience(unsigned experience) {
		if (experience < 60)
			this->experience = experience;
		else
			this->experience = 0;
	}
	void setName(const char* name) {
		if (!name || strlen(name) >= 50)
			strcpy(this->name, "");
		else
			strcpy(this->name, name);
	}

	int getAge() const {
		return age;
	}
	int getExperience() const {
		return experience;
	}
	const char* getName() const {
		return name;
	}
};
