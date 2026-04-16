# ООП - Практикум 16.04.2025 - Седмица 8

**Задача 1:**

Да се напише функция за сортиране на произволен контейнер по подаден компаратор. Направете го чрез подаване на тип на итератор и чрез подаване на тип на контейнер(допускаме, че контейнерът има дефинирани методи begin и end).

**Задача 2:**

За всеки от класовете долу определете дали има нужда от голяма четворка, защо? Правилни ли са декларациите на функциите в тях(спазвани ли са добрите практики), защо?

```c++
class Point{
	int x;
	int y;
	
public:
	Point() = default;
	Point(int x, int y);
	
	int getX();
	int getY();
	
	void setX(const int& x);
	void setY(const int& y);
	
	//поелементно събиране и изваждане
	Point operator+(Point other);
	Point operator+=(Point other);
	Point operator-(Point other);
	Point operator-=(Point other);
	
	//умножение със скалар
	Point operator*(int number);
	Point operator*=(int number);
};

Point::Point(int x, int y) : x(x), y(y) {}
```

```c++
template <class T>
class Vec3 {
	T* arr;
	
public:
	Vec3();
	//скаларно произведение
	const T& dotProduct(Vec3 other) const; 
};

Vec3::Vec3() : arr(new T[3]) {};
```
```c++
template <size_t N>
class StringN{
	char string[N];
	size_t size;
public:
	StringN(char* str, size_t n) : size(std::min(n, N)){
		strncpy(string, str, size);
	}
	
	char* const getString() const;
	size_t const getSize() const;
};
```

```c++
template <class K, class V>
class Record{
	K key;
	V value;
	
public:
	Record(const K& key, const V& value);
	K getKey() const;
	V getValue() const;
	
	void setKey(const K key);
	void setValue(const V value);
};

Record::Record(const K& key, const V& value) : key(key), value(value) {};
```

```c++
class FileStream{
	std::fstream stream;
	
public:
	FileStream(const char* filename, int options);
	
	FileStream write(const char* source, size_t size);
	FileStream read(const char* dest, size_t size);
	
	operator bool();
	
	template <class T>
	FileStream operator<<(const T& obj);
	
	template <class T>
	FileStream operator>>(const T& obj);
};

FileStream::FileStream(const char* filename, int options) : stream(filename, options) {}
FileStream::operator bool(){
	return !stream.fail();
}
```

```c++
template <class T>
struct Node {
		T data;
		Node* next;

		Node(const T& data, const Node* next = nullptr) : data(data), next(next) {}
	};
```

```c++
template <class T, size_t N>
class Vector{
	T arr[N];
	T* end;
	
public:
	Vector() : end(arr) {}
	Vector(T* const arr, size_t size) : end(arr + size) {
		...копираме arr в this->arr...
	};
}
```

```c++
template <class T, size_t N>
class Vector{
	T arr[N];
	size_t size;
	
public:
	Vector() : size(0) {}
	Vector(T* const arr, size_t size) : size(size) {
		...копираме arr в this->arr...
	};
}
```
**Задача 3:**

Да се реализира информационна система за магазин. Трябва да има следните функционалности:

* Продукти, които имат име(до 100 символа), размер(3-мерен), тегло, цена, доставчик и категория
* Доставчици, които имат име(до 100 символа) и време за доставка до магазина
* Потребители, които имат име(до 100 символа), пари, и множество от кошници, в които могат да запазват протукти, които искат да закупят заедно с бройката им(напр. 3 възглавници, 1 хавлия, 1 печка)
	* за всяка кошница да бъде възможно:
		* добавяне на продукт;
		* премахване на продукт;
		* прибавяне/намаляне на бройка към съществуващ продукт;
		* намиране на продукт по подаден предикат;
		* намиране на продукт по име;
		* намиране на продукт с максимална цена;
		* сортиране на продуктите по цена;
		* сотриране на продуктите по най-дълга/къса доставка;
		* сортиране на продуктите по бройка;
		* филтриране на продуктите по категория;
		* филтриране на продуктите по подаден интервал за цена;
		* филтриране на продуктите по подаден интервал за бройка;
		* филтриране на продуктите по подаден интервал за време на доставка;
		* изчистване на кошницата;
		* потвърждаване на поръчката;
	* за потребителят да бъде възможно:
		* добавяне на кошница;
		* премахване на кошница;
		* преименуване на кошница;
		* намиране на кошница по подаден предикат;
		* намиране на кошница с максимална/минимална цена;
		* намиране на кошница с максимално/минимално време за доставка;
		* намиране на кошница с максимален/минимален брой продукти;
		* сортиране на кошниците по обща цена на продуктите;
		* сортиране на кошниците по най-дълга/къса доставка;
		* сортиране на кошниците по бройка на продуктите;
		* филтриране на кошниците по подаден интервал за обща цена на продуктите;
		* филтриране на кошниците по подаден интервал за бройка на продуктите;
		* филтриране на кошниците по подаден интервал за време на доставка;
		* добавяне на даден продукт към всички кошници;
		* намиране на продукт с максимална/минимална цена измежду всички кошници;
		* намиране на продукт с най-дълга/най-къса доставка измежду всички кошници;
* Магазин, който съдържа информация за всички продукти и техните бройки в магазина. Да се реализират подходящи методи за лесно намиране на продукти в магазина. Освен това да има следните функционалности:
	* добавяне на продукт към списъка;
	* премахване на продукт от списъка;
	* зареждане на бройка от продукт;
	* продажба на продукт(трябва да е в наличност за да се продаде);
	* време за получаване на бройка от продукт(ако е в наличност се получава веднага, ако не е трябва да се изчака поръчката)
		



