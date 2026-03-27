#include <iostream>
#include <functional>

template <typename T>
void sortBy(T* arr, size_t size, std::function<bool(const T&, const T&)> greaterThan) {
	if (!arr) return;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (greaterThan(arr[j], arr[j + 1])) std::swap(arr[j], arr[j + 1]);
		}
	}
}

int main() {
	int arr[5] = { 5,4,3,2,1 };
	sortBy<int>(arr, 5, [](int x, int y) {return x%2 > y%2; });
	for (int i = 0; i < 5; i++) {
		std::cout << arr[i] << " ";
	}
}