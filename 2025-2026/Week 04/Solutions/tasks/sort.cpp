#include <iostream>

template <class T>
void shiftRightFromTo(T* arr, size_t start, size_t end) {
	for (size_t i = end; i > start; i--) {
		arr[i] = arr[i - 1];
	}
}

template <class T>
void insert(T* arr, size_t end) {
	size_t i = 0;
	while (i < end && arr[end] >= arr[i]) {
		i++;	
	}
	if (arr[end] < arr[i]) {
		T el = arr[end];
		shiftRightFromTo(arr, i, end);
		arr[i] = el;
		return;
	}
}

//Insertion Sort
//сложност по време - O(n^2)
//сложност по памет - O(1)
//стабилен
template <class T>
void sort(T* arr, size_t size) {
	for (size_t i = 1; i < size; i++) {
		insert(arr, i);
	}
}

//Counting Sort
//сложност по време O(n+d)
//сложност по памет O(d)
// n - size, d - най-големият елемент в масива
//стабилен(тази имплементация не е стабилна)
// 
//знаем, че "най-големият" символ е със стойност 256, което е константа
//тогава сложностите по време и по памет стават съответно O(n) и O(1)
// 
//когато не можем да сме сигурни колко е d или колко е n, не е ясно дали Counting Sort е по-добро
//от някоя от другите сортировки, защото сложностите им не са сравними

template <>
void sort<char>(char* arr, size_t size) {
	const size_t CHAR_COUNT = 256;
	unsigned* counter = new unsigned[CHAR_COUNT] {0}; //инициализира масива с нули
	for (size_t i = 0; i < size; i++) {
		counter[arr[i]]++;
	}
	size_t k = 0;
	size_t j = 0;
	for (size_t i = 0; i < CHAR_COUNT; i++) {
		for (j = 0; j < counter[i]; j++) {
			arr[k + j] = i;
		}
		k += j;
	}
	delete[] counter; //освобождаваме заделената памет
	
}
