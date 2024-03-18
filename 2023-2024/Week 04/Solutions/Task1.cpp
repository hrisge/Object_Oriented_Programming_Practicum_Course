#include <iostream>
#pragma warning (disable: 4996)

class Teacher
{
	char* name;
	unsigned age;
	unsigned experience;


public:
	Teacher(const char* name, unsigned age, unsigned experience)
	{
		setName(name);
		setAge(age);
		setExperience(experience);
	}

	~Teacher()
	{
		delete[] name;
		age = 0;
		experience = 0;
	}


	const char* getName() const
	{
		return name;
	}
	unsigned getAge() const
	{
		return age;
	}
	unsigned getExperience() const
	{
		return experience;
	}

	void setName(const char* name)
	{
		if (this->name != nullptr)
			delete[] this->name;

		int len = strlen(name);
		this->name = new char[len + 1];
		strcpy(this->name, name);
	}
	void setAge(unsigned age)
	{
		this->age = age;
	}
	void setExperience(unsigned exp)
	{
		experience = exp;
	}
};


int main()
{

}