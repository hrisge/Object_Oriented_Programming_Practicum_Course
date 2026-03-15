#include <iostream>
#include <fstream>

bool isPrime(int n) {
	if (n < 2) return false;
	for (int i = 2; i < n; i++) {
		if (n % i == 0) return false;
	}
	return true;
}

void getPrimes(std::ifstream& in) {
	std::ofstream out("primes.bin", std::ios::out | std::ios::binary);
	if (!out.is_open() || !in.is_open()) {
		return;
	}
	int prevPos = in.tellg();
	in.seekg(0, std::ios::beg);

	int num = 0;
	while (in.read((char*)&num, sizeof(int))) {
		if (isPrime(num)) out.write((const char*)&num, sizeof(int));
	}

	in.clear(); //трябва да изчистим състоянието на потока, защото след четенето ще остане невалиден
	in.seekg(prevPos, std::ios::beg);
	out.close();
}