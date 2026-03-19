#include <iostream>
#include <functional>

template <class T>
void copy(const T* src, T* dest, size_t l, size_t r) {
	for (size_t i = l; i <= r; i++) {
		dest[i] = src[i];
	}
}

template<class T, class U>
void mergeBy(T* arr, size_t l, size_t m, size_t r, T* buf, std::function<U(const T&)> f) {
	if (l > m || m > r || l > r) return;
	size_t k = l;
	size_t i = l;
	size_t j = m+1;
	while (i <= m && j <= r) {
		if (f(arr[i]) <= f(arr[j])) {
			buf[k] = arr[i];
			i++;
		}
		else {
			buf[k] = arr[j];
			j++;
		}
		k++;
	}
	while (i <= m) {
		buf[k] = arr[i];
		k++;
		i++;
	}
	while (j <= r) {
		buf[k] = arr[j];
		k++;
		j++;
	}
	copy(buf, arr, l, r);
}

//Merge Sort
//сложност по време - О(n*log n)
//сложност по памет - O(n)
//стабилен
//забележете, че r сочи към последният елемент на масива
template <class T, class U>
void mergeSortBy(T* arr, size_t l, size_t r, T* buf, std::function<U(const T&)> f) {
	if (l >= r)return;
	size_t m = l + (r - l) / 2;
	mergeSortBy(arr, l, m, buf, f);
	mergeSortBy(arr, m + 1, r, buf, f);
	mergeBy(arr, l, m, r,buf, f);
}

template <class T, class U>
void sortBy(T* arr, size_t size, std::function<U(const T&)> f) {
	T* buf = new T[size];
	mergeSortBy(arr, 0, size-1, buf, f);
	delete[] buf;
}

int main() {
	int arr[] = { 6,5,4,3,2,1 };
	sortBy<int,int>(arr, 6, [](int x) {return x % 2; });
	//6 4 2 5 3 1
	//в този пример може да наблюдаваме стабилността, защото 6,4 и 2 приемат стойност 0 след ламбда фунцкията
	//и реда им в сортирания масив е запазен(аналогично за 5,3 и 1)
	for (int i = 0; i < 6; i++) {
		std::cout << arr[i] << " ";
	}
}