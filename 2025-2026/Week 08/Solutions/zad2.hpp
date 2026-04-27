#include <iostream>
#include <fstream>

//нямаме динамична памет и няма нужда от Г4
class Point {
	int x;
	int y;

public:
	Point() = default;
	Point(int x, int y);

	// гетърите трябва да са константни
	int getX() const;
	int getY() const;

	// няма нужда от подаване по константна референция за примитивни типове
	void setX(int x);
	void setY(int y);

	//поелементно събиране и изваждане
	// operator+/- не променят текущия обект, така че трябва да са константни
	// operator+=/-= променят текушния обект и няма смисъл да го копираме при връщане
	Point operator+(const Point& other) const;
	Point& operator+=(const Point& other);
	Point operator-(const Point& other) const;
	Point& operator-=(const Point& other);

	//умножение със скалар
	Point operator*(int number) const;
	Point& operator*=(int number);
};

Point::Point(int x, int y) : x(x), y(y) {}

// трябва да има Г4, тъй като в конструктора заделяме динамична памет
template <class T>
class Vec3 {
	T* arr;

public:
	Vec3();
	//скаларно произведение
	// няма как от скаларно произведение да върнем константна референция от функция
	// за скаларно произведение, защото в обшия случай резултата ще се натрупва в променлива,
	// дефинирана във функцията и след края на функцията ще остане висяща референция
	// 
	// Vec3 трябва да се подава по константна референция
	T dotProduct(const Vec3& other) const {
		T result = T();
		for (int i = 0; i < 3; i++) {
			result += arr[i] * other.arr[i];
		}
		return result;
	}
};
template <class T>
Vec3<T>::Vec3() : arr(new T[3]) {};

// няма нужда от Г4, защото имаме само статична памет(нямаме динамично заделяне на памет)
// и няма особености при копирането
template <size_t N>
class StringN {
	char string[N];
	size_t size;
public:
	// const char* str, защото не го променяме
	StringN(const char* str, size_t n) : size(std::min(n, N)) {
		strncpy(string, str, size);
	}

	// искаме съдържанието на масива да е констатно, а не самият указател 
	const char* getString() const;
	// не е смислено да връщаме копие, което е константно
	size_t getSize() const;
};

// няма нужда от Г4, защото нямаме динамично заделена памет
// и няма особености при копиране стига за K и V копирането да е коректно дефинирано
template <class K, class V>
class Record {
	K key;
	V value;

public:
	Record(const K& key, const V& value);
	// K и V, трябва да се връщат по константна референция за да избегнем копиране
	const K& getKey() const;
	const V& getValue() const;

	void setKey(const K& key);
	void setValue(const V& value);
};

template <class K, class V>
Record<K, V>::Record(const K& key, const V& value) : key(key), value(value) {};

// въпреки че няма динамична памет, файловият поток е ресурс, който заделяме
// и трябва да се погрижим за коректното му управление
// трябва да забраним operator= и копиращия конструктор, защото не можем да имаме два
// потока, които са отворили един и същи файл
class FileStream {
	std::fstream stream;

public:
	FileStream(const char* filename, int options);

	//няма как да връщаме по копие, когато имаме забранен копиращ конструктор
	FileStream& write(const char* source, size_t size);
	//dest не може да е константен, защото ще пишем в него
	FileStream& read(char* dest, size_t size);

	// тъй като функцията не променя потока, трябва да е константна
	operator bool() const;

	template <class T>
	FileStream& operator<<(const T& obj);

	// obj не може да е константен, тъй като ще пишем в него
	template <class T>
	FileStream& operator>>(T& obj);
};

FileStream::FileStream(const char* filename, int options) : stream(filename, options) {}
FileStream::operator bool() const {
	return !stream.fail();
}

// няма нужда от Г4, въпреки че пазим указател.
// ние не заделяме динамична памет в този указател и нямаме проблеми при копиране
template <class T>
struct Node {
	T data;
	Node* next;

	Node(const T& data, const Node* next = nullptr) : data(data), next(next) {}
};

// имаме само статична памет и указател end, който сочи към края на масива
// на пръв поглед няма нужда от Г4, но ако се опитаме да копираме такъв обект получаваме следното
// Vector A = [a1, a2, ..., an] <- A.end (сочи след края на масива)
// Vector B = A;			   ^
// B = [a1, a2, ..., an]	 B.end
// масивът се копира коректно, но променливата за край не се и трябва да се погрижим за това
template <class T, size_t N>
class Vector {
	T arr[N];
	T* end;

public:
	Vector() : end(arr) {}
	//const
	Vector(const T* arr, size_t size) : end(arr + size) {
		...копираме arr в this->arr...
	};
};

// няма нужда от Г4 имаме само статична памет и няма особености при копиране
template <class T, size_t N>
class Vector {
	T arr[N];
	size_t size;

public:
	Vector() : size(0) {}
	//const
	Vector(const T* arr, size_t size) : size(size) {
		...копираме arr в this->arr...
	};
};