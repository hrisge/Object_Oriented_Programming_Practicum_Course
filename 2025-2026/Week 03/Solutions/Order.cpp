#include <iostream>
#include <fstream>

enum PizzaType {
	MARGARITA,
	CALZONE,
	BURRATA
};

enum PizzaSize {
	SMALL,
	MEDIUM,
	LARGE
};

struct Pizza {
	PizzaType type;
	PizzaSize size;
	double price;
};

const size_t MAX_CLIENT_NAME_SIZE = 51;
const size_t MAX_PHONE_NUMBER_SIZE = 21;
const size_t MAX_ADDRESS_SIZE = 101;
const size_t MAX_PIZZAS_SIZE = 10;

struct Order {
	char clientName[MAX_CLIENT_NAME_SIZE];
	char phoneNumber[MAX_PHONE_NUMBER_SIZE];
	char address[MAX_ADDRESS_SIZE];
	double price;
	unsigned pizzaCount;
	Pizza pizzas[MAX_PIZZAS_SIZE];
};

size_t strlen(const char* str) {
	size_t i = 0;
	for(;str[i]!='\0';i++){}
	return i;
}


void writeString(std::ostream& out,const char* str) {
	size_t len = strlen(str);
	out.write((const char*)&len, sizeof(size_t));
	out.write(str, len+1); //+1 заради терминиращата 0
}

std::istream& readString(std::istream& in, char* str) {
	size_t len = 0;
	in.read((char*)&len, sizeof(size_t));
	in.read(str, len+1);
	return in;
}

//ако използваме методите на потоците read и write директно за да записваме поръчки също ще работи, но ще използваме много повече памет, защото
//в общия случай масивите, които имаме няма да са запълнени и въпреки това ще се изписват MAX_..._SIZE на брой променливи във файла за всеки масив

//имплементацията отдолу записва само байтовете, които са "важни" с недостатъка, че преди всеки низ записва броя на байтовете, които трябва да прочете
//това може да доведе до използване на повече памет, ако паметта, която се използва за запазване на броя байтове е повече от спестената памет
//(когато повечето записани масиви са с пълен капацитет)
void writeOrder(std::ostream& out, const Order& order) {
	writeString(out, order.clientName);
	writeString(out, order.phoneNumber);
	writeString(out, order.address);
	out.write((const char*)&order.price, sizeof(double));
	out.write((const char*)&order.pizzaCount, sizeof(unsigned));
	out.write((const char*)order.pizzas, order.pizzaCount * sizeof(Pizza));
}

std::istream& readOrder(std::istream& in, Order& order) {
	readString(in, order.clientName);
	readString(in, order.phoneNumber);
	readString(in, order.address);
	in.read((char*)&order.price, sizeof(double));
	in.read((char*)&order.pizzaCount, sizeof(unsigned));
	in.read((char*)order.pizzas, order.pizzaCount * sizeof(Pizza));
	return in;
}

//не може да се направи за константно време, защото размера на записите на Order във файла варира, т.е. fileSize("orders.bin") / sizeof(Order) няма да даде верен резултат 
size_t ordersCount(std::istream& in) {
	unsigned prevPos = in.tellg();
	in.seekg(0, std::ios::beg);
	Order o;
	size_t count = 0;
	//тъй като readOrder връща обратно потока, можем да го ползваме в булев контекст, където се оценява до !in.fail()
	while (readOrder(in, o)) {
		count++;
	}

	in.clear();
	in.seekg(prevPos);
	return count;
}

int strcmp(const char* str1, const char* str2) {
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	if (len1 < len2) return -1;
	else if (len2 < len1) return 1;
	else {
		for (size_t i = 0; i < len1; i++) {
			if (str1[i] > str2[i]) return 1;
			if (str1[i] < str2[i]) return -1;
		}
		return 0;
	}
}

//Bubble Sort
//сложност по време - O(n^2)
//сложност по памен - O(1)
//стабилен
void sortByAddress(Order* orders, size_t size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (strcmp(orders[j].address, orders[j + 1].address) > 0) std::swap(orders[j], orders[j + 1]);
		}
	}
}

void sortOrders(std::istream& in, std::ostream& out) {
	size_t prevPos = in.tellg();
	in.seekg(0, std::ios::beg);

	size_t size = ordersCount(in);
	Order* orders = new Order[size];
	Order o;
	size_t i = 0;
	while(readOrder(in, o)) {
		orders[i] = o;
		i++;
	}
	in.clear();
	in.seekg(prevPos, std::ios::beg);

	sortByAddress(orders, size);

	for (size_t i = 0; i < size; i++) {
		writeOrder(out, orders[i]);
	}

	delete[] orders;
}


/*
тук всички функции приемат произволен поток за вход или изход, повишавйки нивото на абстракция на функциите
това означава, че са приложими в много ситуации, но понякога са по-трудни за използване, по-лесно e да се направи грешка
например в нашия случай: за всяка функция трябва да се подаде файлов поток, който е валиден, иначе не можем да гарантираме, че работят коректно
в някои случаи е удобно да се правят т. нар. wrapper функции, които правят ползването на фунцкията по-лесно в даден контекст, като жертват гъвкавостта ѝ, т. е. специализират я
за конкретната ситуация можем да имаме:

void writeOrder(const Order& order){
	std::ofstream out("orders.bin", std::ios::out | std::ios::app | std::ios::binary);
	if(!out.is_open()) return;
	writeOrder(out, order);
	out.close();
}
и съответно за readOrder и sortOrders(те как ще станат? какъв недостатък, освен намалената гъвкавост, има този вид на writeOrder? може ли да се избегне?)
*/

int main() {
	Pizza margarita = { MARGARITA, LARGE, 5 };
	Pizza calzone = { CALZONE, MEDIUM, 4 };

	std::fstream file("orders.bin", std::ios::out | std::ios::in | std::ios::binary);
	if (!file.is_open()) {
		std::cout << "Failed to open file" << std::endl;
		return -1;
	}

	Order o1 = { "abc", "123456782", "zabc", 9, 2, {margarita, calzone} };
	Order o2 = { "def", "123456791", "yabc", 14, 3, {margarita, calzone, margarita} };
	Order o3 = { "ghi", "123456780", "xabc", 5,1, {margarita}};
	Order o4 = { "jkl", "123456781", "abc", 4,1, {calzone} };

	writeOrder(file, o1);
	writeOrder(file, o2);
	writeOrder(file, o3);
	writeOrder(file, o4);

	std::cout << ordersCount(file) << std::endl; //4

	std::ofstream out("sorted.bin", std::ios::out | std::ios::binary);
	if (!out.is_open()) return -1;

	sortOrders(file, out);

	out.close();

	std::ifstream in("sorted.bin", std::ios::in | std::ios::binary);
	if (!in.is_open()) return -1;

	Order o;
	while (readOrder(in, o)) {
		std::cout << o.address << std::endl;
	}
	//abc, xabc, yabc, zabc

	in.close();

	file.close();
}
