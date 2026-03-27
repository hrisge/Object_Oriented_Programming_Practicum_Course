#include <iostream>
#include <functional>
#pragma warning (disable : 4996)

class Location {
	char* name;
	double x;
	double y;
	char* description;

	//важно е в този метод dest да се подава по референция, иначе функцията няма да работи и ще имаме изтичане на памет
	void copyString(char*& dest, const char* src) {
		if (src == nullptr) dest = nullptr;
		else {
			dest = new char[strlen(src) + 1];
			strcpy(dest, src);
		}
	}

	void copy(const Location& other) {
		copyString(name, other.name);
		copyString(description, other.description);
		x = other.x;
		y = other.y;
	}
	void free() {
		delete[] name;
		delete[] description;
	}

public:
	Location(const char* name, const char* description, double x, double y) {
		copyString(this->name, name);
		copyString(this->description, description);
		this->x = x;
		this->y = y;
	}
	Location(const Location& other) {
		copy(other);
	}
	Location& operator=(const Location& other) {
		if (this == &other) return *this;
		free();
		copy(other);
		return *this;
	}
	~Location() {
		free();
	}

	bool operator==(const Location& other) const{
		if (!name && !other.name) return true;
		else if (!name || !other.name) return false;
		else return strcmp(name, other.name) == 0 && x == other.x && y == other.y;
	}

	bool operator!=(const Location& other) const{
		if (!name && !other.name) return false;
		else if (!name || !other.name) return true;
		else return strcmp(name, other.name) != 0 || x != other.x || y != other.y;
	}

	friend std::ostream& operator<<(std::ostream& out, const Location& location);

	const char* getName() const {
		return name;
	}
	void setName(const char* name) {
		delete[] this->name;
		copyString(this->name, name);
	}
	const char* getDescription() const {
		return description;
	}
	void setDescription(const char* description) {
		delete[] this->description;
		copyString(this->description, description);
	}
	double getX() const {
		return x;
	}
	void setX(double x) {
		this->x = x;
	}
	double getY() const {
		return y;
	}
	void setY(double y) {
		this->y = y;
	}
	//питагорова теорема :)
	double distanceTo(double x, double y) const {
		return sqrt(pow(this->x - x, 2) + pow(this->y - y, 2));
	}

};

std::ostream& operator<<(std::ostream& out, const Location& location) {
	out << location.name << " (" << location.x << ", " << location.y << "): " << location.description;
	return out;
}

class Area {
	Location** locations;
	size_t size;
	size_t capacity;

	void copy(const Area& other) {
		size = other.size;
		capacity = other.capacity;
		locations = new Location* [capacity];
		for (size_t i = 0; i < size; i++) {
			locations[i] = new Location(*other.locations[i]);
		}
	}
	void free() {
		for (int i = 0; i < size; i++) {
			delete locations[i];
		}
		delete[] locations;
	}

	void resize() {
		if (capacity == 0) {
			capacity = 1;
		}
		capacity *= 2;
		Location** newLocations = new Location* [capacity];
		for (size_t i = 0; i < size; i++) {
			newLocations[i] = new Location(*locations[i]);
		}
		delete[] locations;
		locations = newLocations;
	}

	int containsAt(const Location& location) const {
		for (size_t i = 0; i < size; i++) {
			if (*locations[i] == location) return i;
		}
		return -1;
	}
	template <class T>
	Location* minByFrom(size_t ind, const std::function<T(const Location&)>& p) const {
		if (size == 0 || ind >= size) return nullptr;
		Location* result = locations[ind];
		for (size_t i = ind; i < size; i++) {
			if (p(*result) > p(*locations[i])) result = locations[i];
		}
		return result;
	}

	template <class T>
	Location* minBy(const std::function<T(const Location&)>& p) const {
		return minByFrom(0, p);
	}

	//Selection Sort
	template <class T>
	void sortBy(const std::function<T(const Location&)>& p) {
		for (size_t i = 0; i < size; i++) {
			std::swap(*locations[i], *minByFrom(i, p));
		}
	}

	void removeAt(size_t index) {
		if (index < 0 || index >= size) return;
		delete locations[index];
		std::swap(locations[index], locations[size - 1]);
		size--;
	}

	void filter(const std::function<bool(const Location&)>& p) {
		for (size_t i = 0; i < size; i++) {
			if (!p(*locations[i])){
				removeAt(i);
				//трябва да намаляме i, защотото след като премахнем локацията на позиция i, тя се запълва с нова непроверена локация
				i--;
			}
		}
	}

	void map(const std::function<Location& (Location&)>& f) {
		for (size_t i = 0; i < size; i++) {
			*locations[i] = f(*locations[i]);
		}
	}

public:
	Area() : locations(nullptr), size(0), capacity(0) {}
	Area(const Area& other) {
		copy(other);
	}
	Area& operator=(const Area& other) {
		if (this == &other) return *this;
		free();
		copy(other);
		return *this;
	}
	~Area() {
		free();
	}
	void addLocation(const Location& location) {
		//грижим се локациите да са уникални
		if (containsAt(location) != -1) return;
		if (size >= capacity) {
			resize();
		}
		locations[size++] = new Location(location);
	}
	void removeLocation(const Location& location) {
		int index = containsAt(location);
		removeAt(index);
	}

	//важно е да има константни и неконстантни версии на методите, защото бихме искали
	//да ги извикваме и за константни обекти 
	Location& operator[](size_t ind) {
		return *locations[ind];
	}
	const Location& operator[](size_t ind) const {
		return *locations[ind];
	}
	Area operator+(const Area& other) const {
		Area result;
		for (size_t i = 0; i < size; i++) {
			result.addLocation(*locations[i]);
		}
		for (size_t i = 0; i < other.size; i++) {
			result.addLocation(other[i]);
		}
		return result;
	}
	friend std::ostream& operator<<(std::ostream& out, const Area& area);

	//в методите find може да получим nullptr exception, ако търсим в празен масив, но
	//не сме учили изключения така че нека да гърми
	const Location& findClosest(double x, double y) const {
		return *minBy<double>([x, y](const Location& l) {return l.distanceTo(x, y); });
	}
	Location& findClosest(double x, double y) {
		return *minBy<double>([x, y](const Location& l) {return l.distanceTo(x, y); });
	}
	const Location& findFarthest(double x, double y) const {
		return *minBy<double>([x, y](const Location& l) {return -l.distanceTo(x, y); });
	}
	Location& findFarthest(double x, double y) {
		return *minBy<double>([x, y](const Location& l) {return -l.distanceTo(x, y); });
	}
	const Location& findByDistanceFrom(double x, double y, double distance) const {
		return *minBy<double>([x, y, distance](const Location& l) {return distance - l.distanceTo(x, y); });
	}
	Location& findByDistanceFrom(double x, double y, double distance) {
		return *minBy<double>([x, y, distance](const Location& l) {return distance - l.distanceTo(x, y); });
	}

	Area& sortClosest(double x, double y) {
		sortBy<double>([x, y](const Location& l) {return l.distanceTo(x, y); });
		return *this;
	}
	Area& sortFarthest(double x, double y) {
		sortBy<double>([x, y](const Location& l) {return -l.distanceTo(x, y); });
		return *this;
	}
	Area& sortNameLength() {
		sortBy<size_t>([](const Location& l) {return l.getName() ? strlen(l.getName()) : 0; });
		return *this;
	}
	Area& sortDescriptionLength() {
		sortBy<size_t>([](const Location& l) {return l.getDescription() ? strlen(l.getDescription()) : 0; });
		return *this;
	}
	Area& inCircle(double x, double y, double r) {
		filter([x, y, r](const Location& l) {return l.distanceTo(x, y) <= r; });
		return *this;
	}
	Area& outsideCircle(double x, double y, double r) {
		filter([x, y, r](const Location& l) {return l.distanceTo(x, y) > r; });
		return *this;
	}
	Area& shrink(double x, double y, double c) {
		if (c < 0 || c > 1) return *this;
		map([x, y, c](Location& l) -> Location& {
			double vecX = l.getX() - x;
			double vecY = l.getY() - y;
			l.setX(l.getX() - (vecX / 2) * c);
			l.setY(l.getY() - (vecY / 2) * c);
			return l;
			});
		return *this;
	}
	Area& expand(double x, double y, double c) {
		if (c < 0 || c > 1) return *this;
		map([x, y, c](Location& l) -> Location& {
			double vecX = l.getX() - x;
			double vecY = l.getY() - y;
			l.setX(l.getX() + vecX * c);
			l.setY(l.getY() + vecY * c);
			return l;
			});
		return *this;
	}

	Area& makePath() {
		for (int i = 0; i < size-1; i++) {
			//забележете, че когато искаме да използваме полета на класа в ламбда функция
			//трябва да подаваме this в capture-а
			Location* closest = minByFrom<double>(i + 1, [this, i](const Location& l) {
				return locations[i]->distanceTo(l.getX(), l.getY());
				});
			std::swap(*locations[i + 1], *closest);
		}
		return *this;
	}
};

std::ostream& operator<<(std::ostream& out, const Area& area) {
	for (size_t i = 0; i < area.size; i++) {
		out << area[i] << std::endl;
	}
	return out;
}