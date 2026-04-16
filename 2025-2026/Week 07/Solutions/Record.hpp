#pragma once
#include <iostream>

template <class K, class V>
class Record {
	K key;
public:
	V value;
	const K& getKey() const;
	Record(const K& key, const V& value);
	Record(std::istream& in);
	bool operator==(const Record& other);
	friend std::ostream& operator<<(std::ostream& out, const Record<K, V>& record) {
		out << record.key << "\n" << record.value;
		return out;
	}
	friend std::istream& operator>>(std::istream& in, Record<K, V>& record) {
		in >> record.key >> record.value;
		return in;
	}
};

template<class K, class V>
const K& Record<K, V>::getKey() const
{
	return key;
}

template<class K, class V>
Record<K, V>::Record(const K& key, const V& value) : key(key), value(value) {}

template<class K, class V>
Record<K, V>::Record(std::istream& in) {
	in >> *this;
}

template<class K, class V>
bool Record<K, V>::operator==(const Record& other)
{
	return key == other.key && value == other.value;
}

template<class K, class V>
std::ostream& operator<<(std::ostream& out, const Record<K, V>& record) {
	out << record.key << "\n" << record.value;
	return out;
}

template<class K, class V>
std::istream& operator>>(std::istream& in, Record<K, V>& record) {
	in >> record.key >> record.value;
	return in;
}