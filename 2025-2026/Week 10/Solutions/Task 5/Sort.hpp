#pragma once
#include <functional>

// взимаме първия елемент за pivot
// искаме всички елементи по-малки от него да са от ляво 
// и всички елементи по-големи от него да са отдясно
// накрая връщаме позицията на pivot
// 
// тъй като не знаем точната имплементация на итераторите, ще използваме само минималните им
// функционалности

// partition има времева сложност O(n)
template <class IteratorType, class T>
IteratorType partition(const IteratorType& begin, const IteratorType& end, const std::function<bool(const T&, const T&)>& lessThan) {
	IteratorType pivotPos = begin;

	// с iter ще обхождаме контейнера след pivotPos
	IteratorType iter = pivotPos;

	while (iter != end) {
		// ако елемента на позиция iter е по-малък от pivot
		// ще го поставим отляво на pivot
		if (lessThan(*iter, *pivotPos)) {
			// преместваме pivot с едно напред,като пазим предишната позиция в temp
			IteratorType temp = pivotPos;
			++pivotPos;
			std::swap(*temp, *pivotPos);
			
			// ако iter == pivotPos след като сме го отместили напред,
			// то вече сме разменили необходимите елементи

			// ако iter != pivotPos, трябва да поставим елемента на позиция iter 
			// на позицията преди pivotPos (позицията temp)
			if(iter != pivotPos)
				std::swap(*temp, *iter);	
		}
		++iter;
	}
	return pivotPos;
}

// QuickSort
// сложност по време - O(n * log n) в средния случай
//					 - О(n^2) в най-лошия случай в тази имплементация
// 
// сложност по памет - О(1)
// 
// съществува имплементация, която има времева сложност O(n * log n) в най-лошият случай, 
// но обикновено ако искаме да гарантираме бърза сортировка (със сложност О(n * log n)) 
// използваме MergeSort или HeapSort  
//
// най-лошият случай за QuickSort е когато за pivot се избера винаги максимален или минимален елемент
// (помислете защо)
template <class IteratorType, class T>
void quickSort(const IteratorType& begin, const IteratorType& end, const std::function<bool(const T&, const T&)>& lessThan) {
	if (begin == end) return;
	IteratorType pivot = partition(begin, end, lessThan);

	// разделяме масива спрямо pivot-a и сортираме двете му половини
	quickSort(begin, pivot, lessThan);
	quickSort(++pivot, end, lessThan);
}

template <class ContainerType, class T>
void quickSort(ContainerType& arr, const std::function<bool(const T&, const T&)>& lessThan) {
	quickSort(arr.begin(), arr.end(), lessThan);
}


/*
* имаме възможност да го ползваме дори по такъв начин
* обикновените указатели имат всички нужни методи за да ги използваме като итератори

int main() {
	int arr[] = { 6,5,4,3,2,1,20,-1,3,15,-10,5,4,2,10 };

	quickSort<int*, int>(arr, arr + 15, [](int a, int b) {return a < b; });

	for (int i = 0; i < 15; i++) {
		std::cout << arr[i] << " ";
	}
}
*/