#pragma once
#include <iostream>
#include <functional>
#include <stdexcept>

template <class T>
class LinkedList {

	// въпреки, че в Node пазим указател към динамична памет, тя не се заделя 
	// в Node и съответно той не трябва да се грижи за нея
	struct Node {
		T data;
		Node* next;

		Node(const T& data, Node* next = nullptr);
	};

	Node* start;
	Node* end;
	size_t m_size;

	void copy(const LinkedList& other);;
	//рекурсивен метод за освобождаване на паметта в свързания списък
	void free(Node* node);
	void free();
	void reverse(Node* node);
	//намира Node-ът, който се намира дадения индекс
	const Node* find(size_t ind) const;
	Node* find(size_t ind);
public:
	LinkedList();
	LinkedList(const LinkedList& other);
	LinkedList(const T* arr, size_t size);
	LinkedList& operator=(const LinkedList& other);
	~LinkedList();
	bool empty();
	size_t size() const;
	void push_front(const T& data);
	void pop_front();
	void push_back(const T& data);
	void insertAfter(size_t ind, const T& data);
	void insertAt(size_t ind, const T& data);
	void removeAt(size_t ind);
	//премахва първия елемент, който изпълнява условието
	void removeElement(const std::function<bool(const T&)>& f);
	T& get(size_t ind);
	const T& get(size_t ind) const;
	//за линейно време с копиране
	LinkedList& concat(const LinkedList& other);
	//за константно време с "преместване"
	LinkedList& concat(LinkedList&& other);
	template <class R>
	LinkedList<R> map(const std::function<R(const T&)>& f) const;
	const LinkedList& foreach(const std::function<void(const T&)>& f) const;
	LinkedList& foreach(const std::function<void(T&)>& f);
	LinkedList filter(const std::function<bool(const T&)>& f) const;
	T& find(const std::function<bool(const T&)>& f);
	const T& find(const std::function<bool(const T&)>& f) const;
	LinkedList sortBy(const std::function<bool(const T&, const T&)>& lessThan) const;
	LinkedList& reverse();
	void print() const;
};

template<class T>
LinkedList<T>::Node::Node(const T& data, typename Node* next) : data(data), next(next) {}

template<class T>
void LinkedList<T>::copy(const LinkedList& other) {
	Node* iter = other.start;
	while (iter) {
		push_back(iter->data);
		iter = iter->next;
	}
}

//рекурсивен метод за освобождаване на паметта в свързания списък
template<class T>
void LinkedList<T>::free(Node* node) {
	if (!node) return;
	free(node->next);
	delete node;
	node = nullptr;
}

template<class T>
void LinkedList<T>::free() {
	free(start);
}

// след извикване на този метод имаме такава ситуация
// start <-> next <- ... <- end
// така че е задължително след това да пренасочим по следния начин
// nullptr <- start <- ... <- end
// и след това да разменим start и end
template<class T>
void LinkedList<T>::reverse(Node* node) {
	if (!node || !node->next) {
		return;
	}
	reverse(node->next);
	node->next->next = node;
}

//намира Node-а, който се намира дадения индекс
template<class T>
const typename LinkedList<T>::Node* LinkedList<T>::find(size_t ind) const {
	if (ind > m_size || ind < 0) throw std::out_of_range("Index is out of range");
	Node* iter = start;
	size_t i = 0;
	while (iter && i < ind) {
		iter = iter->next;
		i++;
	}
	return iter;
}

template<class T>
typename LinkedList<T>::Node* LinkedList<T>::find(size_t ind) {
	Node* iter = start;
	size_t i = 0;
	while (iter && i < ind) {
		iter = iter->next;
		i++;
	}
	return iter;
}

template<class T>
LinkedList<T>::LinkedList() : start(nullptr), end(nullptr), m_size(0) {}

template<class T>
LinkedList<T>::LinkedList(const LinkedList& other) { copy(other); }

template<class T>
LinkedList<T>::LinkedList(const T* arr, size_t size) {
	for (size_t i = 0; i < size; i++) {
		push_back(arr[i]);
	}
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
	if (this == &other) return *this;
	free();
	copy(other);
	return *this;
}

template<class T>
LinkedList<T>::~LinkedList() {
	free();
}

template<class T>
bool LinkedList<T>::empty() {
	return !start;
}

template<class T>
size_t LinkedList<T>::size() const {
	return m_size;
}

template<class T>
void LinkedList<T>::push_front(const T& data) {
	if (empty()) {
		start = new Node(data);
		end = start;
		m_size++;
		return;
	}
	Node* node = new Node(data, start);
	start = node;
	m_size++;
}

template<class T>
void LinkedList<T>::pop_front() {
	if (empty()) return;
	//когато е останал само един елемент трябва да занулим указателите след като го изтрием
	if (start == end) {
		delete start;
		start = nullptr;
		end = nullptr;
		m_size--;
		return;
	}
	Node* next = start->next;
	delete start;
	start = next;
	m_size--;
}

template<class T>
void LinkedList<T>::push_back(const T& data) {
	if (empty()) {
		push_front(data);
		return;
	}
	end->next = new Node(data);
	end = end->next;
	m_size++;
}

template<class T>
void LinkedList<T>::insertAfter(size_t ind, const T& data) {
	if (empty() || ind == 0) {
		push_front(data);
		return;
	}
	if (ind == m_size - 1) {
		push_back(data);
		return;
	}
	
	Node* node = find(ind);
	node->next = new Node(data, node->next);
}

template<class T>
void LinkedList<T>::insertAt(size_t ind, const T& data) {
	if (ind == 0) {
		push_front(data);
		return;
	}
	insertAfter(ind - 1, data);
}

template<class T>
void LinkedList<T>::removeAt(size_t ind) {
	if (ind == 0) {
		pop_front();
		return;
	}
	Node* node = find(ind - 1);
	Node* toDelete = node->next;
	// трябва да се погрижим края на списъка да сочи правилния Node
	if (toDelete == end) end = node;
	node->next = node->next->next;
	delete toDelete;
}

template<class T>
void LinkedList<T>::removeElement(const std::function<bool(const T&)>& f)
{
	Node* iter = start;
	size_t i = 0;
	while (iter) {
		if (f(iter->data)) {
			removeAt(i);
			return;
		}
		iter = iter->next;
		i++;
	}
	throw std::runtime_error("Element not found");
}

template<class T>
T& LinkedList<T>::get(size_t ind) {
	return find(ind)->data;
}

template<class T>
const T& LinkedList<T>::get(size_t ind) const {
	return find(ind)->data;
}

//за линейно време с копиране
template<class T>
LinkedList<T>& LinkedList<T>::concat(const LinkedList<T>& other) {
	if (this != &other) {
		/*
		Node* iter = other.start;
		while (iter) {
		push_back(iter->data);
		}
		всеки цикъл от такъв тип може да бъде заменен с foreach
		*/

		other.foreach([this](const T& el) {this->push_back(el); });
	}
	else {
		concat(LinkedList(other));
	}
	return *this;
}

//за константно време с "преместване"
template<class T>
LinkedList<T>& LinkedList<T>::concat(LinkedList<T>&& other) {
	if (this != &other) {
		end->next = other.start;
		end = other.end;
		m_size += other.m_size;
		// трябва да се погрижим другия списък да няма достъп до данните си
		// след това, защото не искаме да имаме споделена памет
		// все едно крадем данните от другия списък
		other.start = nullptr;
		other.end = nullptr;
		other.m_size = 0;
	}
	else {
		concat(LinkedList(other));
	}
	return *this;
}

// foreach изпълнява дадена функция, която не връща резултат, върху всеки елемент
// подобно е на map, но можем да го използваме като абстракция за цикъл
// използваме го за да преизползваме код(не ми се пишат цикли за свързан списък) 
template<class T>
const LinkedList<T>& LinkedList<T>::foreach(const std::function<void(const T&)>& f) const {
	Node* iter = start;
	while (iter) {
		f(iter->data);
		iter = iter->next;
	}
	return *this;
}

template<class T>
LinkedList<T>& LinkedList<T>::foreach(const std::function<void(T&)>& f) {
	Node* iter = start;
	while (iter) {
		f(iter->data);
		iter = iter->next;
	}
	return *this;
}

template<class T>
LinkedList<T> LinkedList<T>::filter(const std::function<bool(const T&)>& f) const {
	LinkedList<T> result;
	foreach([&result, &f](const T& el) {if (f(el)) result.push_back(el); });
	return result;
}

template<class T>
T& LinkedList<T>::find(const std::function<bool(const T&)>& f)
{
	Node* iter = start;
	while (iter) {
		if (f(iter->data)) return iter->data;
		iter = iter->next;
	}
	throw std::runtime_error("Element not found");
}

template<class T>
const T& LinkedList<T>::find(const std::function<bool(const T&)>& f) const
{
	Node* iter = start;
	while (iter) {
		if (f(iter->data)) return iter->data;
		iter = iter->next;
	}
	throw std::runtime_error("Element not found");
}

//Bubble Sort
template<class T>
LinkedList<T> LinkedList<T>::sortBy(const std::function<bool(const T&, const T&)>& lessThan) const {
	LinkedList result(*this);
	for (size_t i = 0; i < m_size; i++) {
		size_t j = 0;
		for (Node* iter = result.start; iter && iter->next && j < m_size - i; iter = iter->next) {
			if (lessThan(iter->next->data, iter->data)) std::swap(iter->data, iter->next->data);
			j++;
		}
	}
	return result;
}

template<class T>
LinkedList<T>& LinkedList<T>::reverse() {
	reverse(start);
	start->next = nullptr;
	std::swap(start, end);
	return *this;
}

template<class T>
void LinkedList<T>::print() const {
	foreach([](const T& el) {std::cout << el << " "; });
}

template<class T>
template<class R>
LinkedList<R> LinkedList<T>::map(const std::function<R(const T&)>& f) const {
	LinkedList<R> result;
	foreach([&result, &f](const T& el) {result.push_back(f(el)); });
	return result;
}

/*
за какво време ще се изпълни това обхождане на свързания спсък?
for(size_t i = 0 ; i < m_size; i++){
	T element = get(i);
}
*/