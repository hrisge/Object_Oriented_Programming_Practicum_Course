#pragma once
#pragma warning (disable : 4996)
#include "Record.hpp"
#include <fstream>
#include <functional>
#include "LinkedList.hpp"

template <class K, class V>
class Repository {
	std::fstream stream;
	char* filename;
	Record<K, V> defaultRecord;
	size_t fileSize();
	void reset();

public:
	// в случай, че K или V няма default конструктор, ще трябва да се подаде стойност, която
	// да се използва по подразбиране
	Repository(const char* filename, const Record<K,V>& defaultRecord = Record<K,V>(K(), V()));
	Repository(const Repository&) = delete;
	Repository& operator=(const Repository&) = delete;
	~Repository();

	bool empty();
	size_t count();
	void add(const K& key, const V& value); 
	void add(const Record<K,V>& record);
	Record<K,V> get(const K& key);
	Record<K, V> get(const std::function<bool(const Record<K, V>&)>& f);
	void update(const Record<K, V>& record);
	LinkedList<Record<K, V>> getAll();
	LinkedList<Record<K, V>> getAll(const std::function<bool(const Record<K, V>&)>& f);
	void remove(const K& value);
};

template<class K, class V>
size_t Repository<K, V>::fileSize() {
	size_t oldPos = stream.tellg();
	stream.seekg(0, std::ios::end);
	size_t size = stream.tellg();
	stream.seekg(oldPos, std::ios::beg);
	return size;
}

template<class K, class V>
void Repository<K, V>::reset()
{
	stream.clear();
	stream.seekg(0, std::ios::beg);
	stream.seekp(0, std::ios::beg);
}

template<class K, class V>
Repository<K, V>::Repository(const char* filename, const Record<K,V>& defaultRecord) 
	: stream(filename, std::ios::in | std::ios::out | std::ios::app), defaultRecord(defaultRecord)
{
	if (!stream.is_open()) {
		throw std::invalid_argument("Invalid filename");
	}
	this->filename = new char[strlen(filename) + 1];
	strcpy(this->filename, filename);
}

template<class K, class V>
Repository<K, V>::~Repository()
{
	stream.close();
	delete[] filename;
}

template<class K, class V>
bool Repository<K, V>::empty()
{
	return fileSize() == 0;
}

template<class K, class V>
size_t Repository<K, V>::count()
{

	size_t count = 0;
	Record<K, V> rec(defaultRecord);
	while (stream >> rec) {
		count++;
	}
	reset();
	return count;
}

template<class K, class V>
void Repository<K, V>::add(const K& key, const V& value)
{
	add(Record<K, V>(key, value));
}

template<class K, class V>
void Repository<K, V>::add(const Record<K, V>& record)
{
	// ако елементът не съществува ще прихванем грешката от get и ще го създадем, иначе ще хвърлим грешка,
	// че елемент с този ключ вече съществува
	try {
		get(record.getKey());
		throw std::invalid_argument("Element with this key already exists");
	}
	catch (std::runtime_error e) {
		stream.seekp(0, std::ios::end);
		stream << record << "\n";
		reset();
	}
}
	

template<class K, class V>
Record<K, V> Repository<K, V>::get(const K& key)
{
	return get([&](const Record<K, V>& record) {return record.getKey() == key; });
}

template<class K, class V>
Record<K, V> Repository<K, V>::get(const std::function<bool(const Record<K, V>&)>& f)
{
	//обхождаме всички записи и проверяваме дали всеки от тях отговаря на условието
	Record<K, V> record(defaultRecord);
	while (stream >> record) {
		if (f(record)) {
			reset();
			return record;
		}
	}
	reset();
	throw std::runtime_error("No element found");
}

template<class K, class V>
void Repository<K, V>::update(const Record<K, V>& record)
{
	// ще хвърли грешка ако елемента не съществува
	get(record.getKey());

	std::ofstream out("temp.txt");
	if (!out) throw std::runtime_error("Cannot create temp file");
	
	//записваме всичко във временен файл, като променяме записа, чийто ключ съвпада с подадения
	Record<K, V> tempRecord(defaultRecord);
	while (stream >> tempRecord) {
		if (tempRecord.getKey() != record.getKey()) {
			out << tempRecord << "\n";
		}
		else {
			out << record << "\n";
		}
	}
	out.close();
	stream.close();
	//изчистваме файла, с който сме работим
	stream.open(filename, std::ios::out | std::ios::in | std::ios::trunc);
	if (!stream.is_open()) throw std::runtime_error("Cannot open repository file");
	stream.seekp(0, std::ios::beg);
	
	std::ifstream in("temp.txt");
	if(!in.is_open()) throw std::runtime_error("Cannot open repository file");
	
	//копираме всички записи от временния файл във файла, с който работим
	while (in >> tempRecord) {
		stream << tempRecord << "\n";
	}

	reset();
	in.close();
}

template<class K, class V>
LinkedList<Record<K, V>> Repository<K, V>::getAll()
{
	LinkedList<Record<K, V>> result;
	Record<K, V> record(defaultRecord);
	while (stream >> record) {
		result.push_back(record);
	}
	reset();
	return result;
	
}

template<class K, class V>
LinkedList<Record<K, V>> Repository<K, V>::getAll(const std::function<bool(const Record<K, V>&)>& f)
{
	LinkedList<Record<K, V>> result;
	Record<K, V> record(defaultRecord);
	while (stream >> record) {
		if (f(record)) result.push_back(record);
	}
	reset();
	return result;
}

// подобно на update трябва да копираме всички записи освен този, който
// искаме да изтрием, във временен файл и след това да ги преместим обратно
// във файла, с който работим
template<class K, class V>
void Repository<K, V>::remove(const K& key)
{
	// ще хвърли грешка ако елемента не съществува
	get(key);

	std::ofstream out("temp.txt");
	if (!out) throw std::runtime_error("Cannot create temp file");
	Record<K, V> record(defaultRecord);
	while (stream >> record) {
		if (record.getKey() != key) {
			out << record << "\n";
		}
	}
	out.close();

	std::ifstream in("temp.txt");
	stream.close();
	stream.open(filename, std::ios::out | std::ios::in | std::ios::trunc);

	stream.seekp(0, std::ios::beg);
	in.seekg(0, std::ios::beg);
	while (in >> record) {
		stream << record << "\n";
	}

	reset();
	in.close();
}
