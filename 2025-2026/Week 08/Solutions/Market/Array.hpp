#pragma once
#include <functional>
#include "Sort.hpp"
#include <stdexcept>

//преоразмеряващ се масив
template <class T>
class Array {
	T* array;
	size_t m_size;
	size_t capacity;

	void copy(const Array& other);
	void free();
	void resize();
	
public:
	Array();
	Array(const Array& other);
	Array& operator=(const Array& other);
	~Array();

	// минимална реализация за итератор
	// може да се добавят и още оператори за удобство(напр. +/-, +/-=, < ,<=, >, >=)
	class iterator {
		T* pos;
	public:
		iterator(T* pos) : pos(pos) {}

		iterator& operator++();
		const T& operator*() const;
		T& operator*();
		bool operator==(const iterator& other) const;
		bool operator!=(const iterator& other) const;
		bool isValid() const;
		operator bool() const;
	};

	class const_iterator {
		const T* pos;
	public:
		const_iterator(const T* pos) : pos(pos) {}
		const_iterator(const iterator& it) : pos(it.pos) {}

		const_iterator& operator++();
		const T& operator*() const;
		bool operator==(const const_iterator& other) const;
		bool operator!=(const const_iterator& other) const;
		bool isValid() const;
		operator bool() const;
	};

	// operator* на iterator връща референция към обекта на позицията
	// това означава, че е възможно да бъде променен и въпреки че
	// begin и end не променят директно масива, те не трябва да са константни

	iterator begin();
	iterator end();

	// ако все пак искаме да можем да итерираме през константен масив
	// трябва да си направим друг итератор, който ще пази стойността
	// на позицията константна

	const_iterator begin() const;
	const_iterator end() const;

	bool empty() const;
	size_t size() const;

	void push_back(const T& element);
	void pop_back();

	template <class R>
	Array<R> map(const std::function<R(const T&)>& f) const;
	Array filter(const std::function<bool(const T&)>& f) const;
	Array sortBy(const std::function<bool(const T&, const T&)>& comp = [](const T& a, const T& b) {return a < b; }) const;

	// сортиране по подадено свойство на елемента
	template <class U>
	Array sortBy(const std::function<U(const T&)>& prop = [](const T& a) {return a; }) const;

	Array reverse() const;

	// премахва първия елемент, който изпълнява условието
	void remove_first(const std::function<bool(const T&)>& f = [](const T&) {return true; });

	// константен и неконстантен оператор за индексиране
	T& operator[](size_t ind);
	const T& operator[](size_t ind) const;

	// намира първия елемент, който изпълнява условието и хвърля грешка ако няма такъв
	// константно и неконстантно
	T& find(const std::function<bool(const T&)>& f);
	const T& find(const std::function<bool(const T&)>& f) const;

	// връща първата позиция, за която елемента изпълнява условието
	iterator findPos(const std::function<bool(const T&)>& f);
	const_iterator findPos(const std::function<bool(const T&)>& f) const;

	// методи за намиране на мин и макс по подадено свойство на елемента
	// хвърлят грешка, ако масива е празен
	template <class U>
	T& max(const std::function<U(const T&)>& f = [](const T& el) {return el; });
	template <class U>
	const T& max(const std::function<U(const T&)>& f = [](const T& el) {return el; }) const;
	template <class U>
	T& min(const std::function<U(const T&)>& f = [](const T& el) {return el; });
	template <class U>
	const T& min(const std::function<U(const T&)>& f = [](const T& el) {return el; }) const;
};


template<class T>
void Array<T>::copy(const Array& other)
{
	m_size = other.m_size;
	capacity = other.capacity;
	this->array = new T[capacity];
	for (size_t i = 0; i < m_size; i++) {
		this->array[i] = other.array[i];
	}
}

template<class T>
void Array<T>::free()
{
	delete[] this->array;
}

template<class T>
void Array<T>::resize()
{
	if (capacity == 0) capacity = 1;
	capacity *= 2;
	T* newArr = new T[capacity];
	for (size_t i = 0; i < size(); i++) {
		newArr[i] = array[i];
	}
	delete[] array;
	array = newArr;
}

template<class T>
typename Array<T>::iterator& Array<T>::iterator::operator++()
{
	++pos;
	return *this;
}

template<class T>
const T& Array<T>::iterator::operator*() const
{
	return *pos;
}

template<class T>
T& Array<T>::iterator::operator*()
{
	return *pos;
}

template<class T>
bool Array<T>::iterator::operator==(const iterator& other) const
{
	return pos == other.pos;
}

template<class T>
bool Array<T>::iterator::operator!=(const iterator& other) const
{
	return pos != other.pos;
}

template<class T>
bool Array<T>::iterator::isValid() const
{
	return pos;
}

template<class T>
Array<T>::iterator::operator bool() const
{
	return isValid();
}

template<class T>
typename Array<T>::const_iterator& Array<T>::const_iterator::operator++()
{
	++pos;
	return *this;
}

template<class T>
const T& Array<T>::const_iterator::operator*() const
{
	return *pos;
}

template<class T>
bool Array<T>::const_iterator::operator==(const const_iterator& other) const
{
	return pos == other.pos;
}

template<class T>
bool Array<T>::const_iterator::operator!=(const const_iterator& other) const
{
	return pos != other.pos;
}

template<class T>
bool Array<T>::const_iterator::isValid() const
{
	return pos;
}

template<class T>
Array<T>::const_iterator::operator bool() const
{
	return isValid();
}

template<class T>
typename Array<T>::iterator Array<T>::findPos(const std::function<bool(const T&)>& f)
{
	for (iterator i = begin(); i != end(); ++i) {
		if (f(*i)) return i;
	}
	return nullptr;
}

template<class T>
typename Array<T>::const_iterator Array<T>::findPos(const std::function<bool(const T&)>& f) const
{
	for (const_iterator i = begin(); i != end(); ++i) {
		if (f(*i)) return i;
	}
	return nullptr;
}

template<class T>
Array<T>::Array() : array(nullptr), m_size(0), capacity(0) {}

template<class T>
Array<T>::Array(const Array& other)
{
	copy(other);
}

template<class T>
Array<T>& Array<T>::operator=(const Array& other)
{
	if (&other == this) return *this;
	free();
	copy(other);
	return *this;
}

template<class T>
Array<T>::~Array()
{
	free();
}

template<class T>
typename Array<T>::iterator Array<T>::begin()
{
	return array;
}

template<class T>
typename Array<T>::iterator Array<T>::end()
{
	return array+m_size;
}

template<class T>
typename Array<T>::const_iterator Array<T>::begin() const
{
	return array;
}

template<class T>
typename Array<T>::const_iterator Array<T>::end() const
{
	return array+m_size;
}

template<class T>
bool Array<T>::empty() const
{
	return size() == 0;
}

template<class T>
size_t Array<T>::size() const
{
	return m_size;
}

template<class T>
void Array<T>::push_back(const T& element)
{
	if (size() >= capacity) {
		resize();
	}
	array[size()] = element;
	m_size++;
}

template<class T>
void Array<T>::pop_back()
{
	m_size--;
}

template<class T>
Array<T> Array<T>::filter(const std::function<bool(const T&)>& f) const
{
	Array<T> result;

	// range-for синтаксис 
	for (const T& el : *this) {
		if (f(el)) result.push_back(el);
	}
	return result;
}

template<class T>
Array<T> Array<T>::sortBy(const std::function<bool(const T&, const T&)>& comp) const
{
	Array<T> result(*this);
	quickSort(result, comp);
	return result;
}

template<class T>
Array<T> Array<T>::reverse() const
{
	Array<T> result(*this);
	for (size_t i = 0; i < m_size / 2; i++) {
		std::swap(result[i], result[m_size - i - 1]);
	}
	return result;
}

template<class T>
void Array<T>::remove_first(const std::function<bool(const T&)>& f)
{
	iterator pos = findPos(f);
	if (!pos) return;
	iterator i = pos;
	++i;
	while (i != end()) {
		std::swap(*pos, *i);
		++pos;
		++i;
	}
	pop_back();
}

template<class T>
T& Array<T>::operator[](size_t ind)
{
	return array[ind];
}

template<class T>
const T& Array<T>::operator[](size_t ind) const
{
	return array[ind];
}

template<class T>
T& Array<T>::find(const std::function<bool(const T&)>& f)
{
	iterator result = findPos(f);
	if (!result) throw std::runtime_error("No element found");
	return *result;
}

template<class T>
const T& Array<T>::find(const std::function<bool(const T&)>& f) const
{
	const_iterator result = findPos(f);
	if (!result) throw std::runtime_error("No element found");
	return *result;
}

template<class T>
template<class R>
Array<R> Array<T>::map(const std::function<R(const T&)>& f) const
{
	Array<R> result;
	for (const T& el : *this) {
		result.push_back(f(el));
	}
	return result;
}

template<class T>
template<class U>
T& Array<T>::max(const std::function<U(const T&)>& f)
{
	if (empty()) throw std::runtime_error("Array is empty");
	size_t maxInd = 0;
	for (size_t i = 1; i < size(); i++) {
		if (f(array[maxInd]) < f(array[i])) maxInd = i;
	}
	return array[maxInd];
}

template<class T>
template<class U>
const T& Array<T>::max(const std::function<U(const T&)>& f) const
{
	if (empty()) throw std::runtime_error("Array is empty");
	size_t maxInd = 0;
	for (size_t i = 1; i < size(); i++) {
		if (f(array[maxInd]) < f(array[i])) maxInd = i;
	}
	return array[maxInd];
}

template<class T>
template<class U>
T& Array<T>::min(const std::function<U(const T&)>& f)
{
	if (empty()) throw std::runtime_error("Array is empty");
	size_t minInd = 0;
	for (size_t i = 1; i < size(); i++) {
		if (f(array[minInd]) > f(array[i])) minInd = i;
	}
	return array[minInd];
}

template<class T>
template<class U>
const T& Array<T>::min(const std::function<U(const T&)>& f) const
{
	if (empty()) throw std::runtime_error("Array is empty");
	size_t minInd = 0;
	for (size_t i = 1; i < size(); i++) {
		if (f(array[minInd]) > f(array[i])) minInd = i;
	}
	return array[minInd];
}

template <class T>
template <class U>
Array<T> Array<T>::sortBy(const std::function<U(const T&)>& prop) const {
	return sortBy([&](const T& a, const T& b) {return prop(a) < prop(b); });
}