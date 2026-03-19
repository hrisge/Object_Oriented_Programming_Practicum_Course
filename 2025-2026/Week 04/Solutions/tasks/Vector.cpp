#include <iostream>
#include <functional>

template <class T, size_t N>
struct Vector {
	T arr[N];
	size_t size;
};

template <class T, class U, size_t N>
Vector<U, N> map(std::function<U(const T&)> f, const Vector<T, N>& vec) {
	Vector<U, N> result;
	result.size = vec.size;
	for (int i = 0; i < vec.size; i++) {
		result.arr[i] = f(vec.arr[i]);
	}
	return result;
}

template <class T, size_t N>
Vector<T, N> filter(std::function<bool(const T&)> f, const Vector<T, N>& vec) {
	Vector<T, N> result;
	for (int i = 0; i < vec.size; i++) {
		if (f(vec.arr[i])) {
			result.arr[result.size] = vec.arr[i];
			result.size++;
		}
	}
	return result;
}

template<class T, size_t N>
bool all(std::function<bool(const T&)> f, const Vector<T, N>& vec) {
	for (size_t i = 0; i < N; i++) {
		if (!f(vec.arr[i])) return false;
	}
	return true;
}

template<class T, size_t N>
bool any(std::function<bool(const T&)> f, const Vector<T, N>& vec) {
	return !all([f](const T& x) {return !f(x);}, vec);
}

template <class T, class U, class V, size_t N>
Vector<V, N> zipWith(std::function<V(const T&, const U&)> op, const Vector<T, N>& vec1, const Vector<V, N>& vec2) {
	Vector<V, N> result;
	result.size = std::min({ vec1.size, vec2.size });
	for (int i = 0; i < result.size; i++) {
		result.arr[i] = op(vec1.arr[i], vec2.arr[i]);
	}
	return result;
}

int main() {
	Vector<int, 10> v1 = { {1,2,3,4,5}, 5 };
	Vector<int, 10> v2 = { {5,4,3,2}, 4 };
	Vector<int, 10> v3 = zipWith<int,int,int>([](int x, int y) {return x * y; }, v1, v2);
	for (int i = 0; i < v3.size; i++) {
		std::cout << v3.arr[i] << " "; // 5 8 9 8
	}
}