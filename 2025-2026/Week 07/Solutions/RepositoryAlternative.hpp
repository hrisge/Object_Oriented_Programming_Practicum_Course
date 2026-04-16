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
	LinkedList<Record<K, V>> list;
	size_t fileSize();
	void reset();
	void saveList();

public:
	Repository(const char* filename, const Record<K, V>& defaultRecord = Record<K,V>(K(), V()));
	Repository(const Repository&) = delete;
	Repository& operator=(const Repository&) = delete;
	~Repository();

	bool empty();
	size_t count();
	void add(const K& key, const V& value);
	void add(const Record<K, V>& record);
	Record<K, V> get(const K& key);
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
Repository<K, V>::Repository(const char* filename, const Record<K, V>& defaultRecord)
	: stream(filename, std::ios::in | std::ios::out | std::ios::app), defaultRecord(defaultRecord)
{
	if (!stream.is_open()) {
		throw std::invalid_argument("Invalid filename");
	}
	this->filename = new char[strlen(filename) + 1];
	strcpy(this->filename, filename);
	Record<K, V> record(defaultRecord);
	while (stream >> record) {
		list.push_back(record);
	}
	reset();
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
	return list.empty();
}

template<class K, class V>
size_t Repository<K, V>::count()
{
	return list.size();
}

template<class K, class V>
void Repository<K, V>::add(const K& key, const V& value)
{
	add(Record<K, V>(key, value));
}

template<class K, class V>
void Repository<K, V>::add(const Record<K, V>& record)
{
	try {
		get(record.getKey());
		throw std::invalid_argument("Element already exists");
	}
	catch (std::runtime_error e) {
		list.push_back(record);
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
	return list.find(f);
}

template<class K, class V>
void Repository<K, V>::update(const Record<K, V>& record)
{
	// ще хвърли грешка ако елемента не съществува
	Record<K, V>& toUpdate = list.find([&](const Record<K, V>& rec) {return rec.getKey() == record.getKey(); });
	toUpdate = record;
	saveList();
	
}

template<class K, class V>
LinkedList<Record<K, V>> Repository<K, V>::getAll()
{
	return list;
}

template<class K, class V>
LinkedList<Record<K, V>> Repository<K, V>::getAll(const std::function<bool(const Record<K, V>&)>& f)
{
	return list.filter(f);
}

template<class K, class V>
void Repository<K, V>::remove(const K& key)
{
	// ще хвърли грешка ако елемента не съществува
	list.removeElement([&](const Record<K, V>& r) {return r.getKey() == key; });
	saveList();
}

template<class K, class V>
void Repository<K, V>::saveList()
{
	stream.close();
	stream.open(filename, std::ios::in | std::ios::out | std::ios::trunc);

	list.foreach([&](const Record<K, V>& r) {
		stream << r << "\n";
	});

	reset();
}

/*
Какви са предимставата и недостатъците на тази имплементация спрямо другата?
*/