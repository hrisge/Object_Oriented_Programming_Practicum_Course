#include <iostream>
#include <functional>

template <class T, class U, class V>
std::function<V(U, T)> flip(std::function<V(T, U)> f) {
	return [f](U y, T x) {return f(x, y); };
}

int main() {
	std::cout << flip<int, int, int>([](int x, int y) {return x % y; })(3, 2) << std::endl; //2
}