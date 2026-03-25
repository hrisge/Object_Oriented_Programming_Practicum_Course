#include <functional>
#include <iostream>

template <class T, class U>
T accumulate(std::function<T(const U&, const T&)> op, const T& nv, std::function<U(int)> term, int a, int b) {
	T result = nv;
	while (a <= b) {
		result = op(term(b), result);
		b--;
	}
	return result;
}

//Бонус:
template <class T>
T* createArrFromRange(int a, int b, std::function<T(int)> term) {
	size_t size = b - a + 1;
	T* arr = new T[size];
	//забележете как използваме capture клаузата на тази ламбда функция
	return accumulate<T*, T>([&size](const T& x, T* arr) {arr[(size--)-1] = x; return arr; }, arr, term, a, b);
}

int* createArrFromRange(int a, int b) {
	return createArrFromRange<int>(a, b, [](int x) {return x; });
}

int main() {
	std::cout << accumulate<int, int>([](int x, int y) {return x + y; }, 0, [](int x) {return x; }, 0, 10)  << std::endl;
	int* arr = createArr<int>(1, 10, [](int x){return x; });
	for (int i = 0; i < 10; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
	delete[] arr;
}