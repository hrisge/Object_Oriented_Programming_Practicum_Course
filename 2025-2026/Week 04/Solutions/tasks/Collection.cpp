#include <iostream>
#include <functional>
#include <fstream>

template <class V, class K>
struct Record {
	K key;
	V value;
};

//Тук може да ни се иска по някакъв начин да кажем, че T трябва да е Record 
//C++ 20 и нагоре поддържат такива ограничения на типовете в шаблона, но това не ни е нужно.
//Ако подадем тип, който не е Record ще получим грешка, във функциите долу,
//понеже ще се опитат да достъпят свойства на Record, които T няма.
//и в двата случая програмата няма да работи, така че нека да гърми при грешен тип :)
template<class T, size_t N>
struct Collection {
	T records[N];
};

template<class T, size_t N>
void readCollection(Collection<T, N>& c, const char* filename) {
	std::ifstream in(filename, std::ios::in);
	if (!in.is_open()) return;
	for (size_t i = 0; i < N && in; i++) {
		in >> c.records[i].key;
		in >> c.records[i].value;
	}
	in.close();
}

template<class T, size_t N>
void writeCollection(const Collection<T, N>& c, const char* filename) {
	std::ofstream out(filename, std::ios::in);
	if (!out.is_open()) return;
	for (size_t i = 0; i < N; i++) {
		out << c.records[i].key << " " << c.records[i].value << '\n';
	}
	out.close();
}

template <class T, size_t N>
T maxRecord(const Collection<T, N>& c) {
	size_t maxInd = 0;
	for (size_t i = 0; i < N; i++) {
		if (c.records[maxInd].value < c.records[i].value) maxInd = i;
	}
	return c.records[maxInd];
}

//използваме sortBy от задача 5

template <class T, size_t N>
void sortByValue(Collection<T, N>& c) {
	sortBy(c.records, N, [](const T& record) {return record.value; });
}

template <class T, size_t N>
int filter(const Collection<T, N>& c, std::function<bool(const T&)> pred) {
	int counter = 0;
	for (int i = 0; i < N; i++) {
		if (pred(c.records[i])) counter++;
	}
	return counter;
}