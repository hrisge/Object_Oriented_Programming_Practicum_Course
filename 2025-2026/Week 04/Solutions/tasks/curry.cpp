#include <functional>
#include <iostream>

template <class T,class U,class V>
std::function<V(U)> curry(std::function<V(T, U)> f, T x) {
	//трябва да подадем f и x в capture клаузата, за да можем да ги ползваме в тялото на ламбдата
	return [f,x](U y){ return f(x, y); };
}

int sum(int a, int b) {
	return a + b;
}

int main() {
	std::cout << curry<int, int, int>(sum, 5)(-3) << std::endl; //2 
}