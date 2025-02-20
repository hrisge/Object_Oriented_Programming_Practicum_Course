# УП - преговор
 
* **УКАЗАТЕЛИ И РЕФЕРЕНЦИИ**
 
**Пример 1: Какво ще се изведе на конзолата?**
```c++
#include <iostream>
 
void modify(int* ptr) {
    *ptr = 20;
}
 
int main() {
    int x = 10;
    int* p = &x;
    modify(p);
    std::cout << x << std::endl;
    return 0;
}
```
 
**Пример 2: Ще се компилира ли кодът? Ако не, защо?**
 
```c++
#include <iostream>
 
int main() {
    int x = 5;
    int& ref;
    ref = x;
 
    std::cout << ref << std::endl;
    return 0;
}
```
**Пример 3: Какво ще се изведе на конзолата?**
 
```c++
#include <iostream>
 
void func(int ref) {
    ref += 5;
}
 
int main() {
    int a = 10;
    func(a);
    std::cout << a << std::endl;
    return 0;
}
```
 
**Пример 4: Ще се компилира ли?**
 
```c++
#include <iostream>
 
int main() {
    int x = 10;
    int* ptr = &x;
    int& ref = *ptr;
 
    ref = 20;
 
    std::cout << x << std::endl;
    return 0;
}
```
 
**Пример 5: Какво ще се изведе на конзолата?**
 
```c++
#include <iostream>
 
void func(int* ptr) {
    ptr = nullptr;
}
 
int main() {
    int x = 42;
    int* p = &x;
 
    func(p);
 
    if (p) {
        std::cout << *p << std::endl;
    } else {
        std::cout << "Pointer is null" << std::endl;
    }
    return 0;
}
```
 
* **ДИНАМИЧНА ПАМЕТ**
 
**Пример 1: Какво ще се изведе на козолата?**
 
```c++
#include <iostream>
 
int main() {
    int* p = new int(10);
    std::cout << *p << std::endl;
    delete p;
    return 0;
}
```
 
**Пример 2: Ще се компилира ли?**
 
```c++
#include <iostream>
 
int main() {
    int* p = new int[5];
    delete p; // Грешка?
    return 0;
}
```
 
**Пример 3: Какво ще се изведе на козолата?**
 
```c++
#include <iostream>
 
int main() {
    int* p = new int(100);
    delete p;
    std::cout << *p << std::endl;
    return 0;
}
```
 
**Пример 4: Ще се компилира ли?**
 
```c++
#include <iostream>
 
void allocate(int*& ptr) {
    ptr = new int(50);
}
 
int main() {
    int* p = nullptr;
    allocate(p);
    std::cout << *p << std::endl;
    delete p;
    return 0;
}
```
 
**Пример 5: Ще се компилира ли?**
 
```c++
#include <iostream>
 
int* func() {
    int x = 10;
    return &x;
}
 
int main() {
    int* p = func();
    std::cout << *p << std::endl;
    return 0;
}
```
 
**Пример 6: Какво ще се изведе на козолата?**
 
```c++
#include <iostream>
 
int main() {
    int* p1 = new int(10);
    int* p2 = p1;
 
    delete p1;
    std::cout << *p2 << std::endl;
    return 0;
}
```

**Задача 1**

Напишете Selection Sort

Можете да видите как рабити алгиритъмът, в случай, че сте забравили, тук:
https://sortvisualizer.com/selectionsort/

**Задача 2**

Напишете Merge sort

Можете да видите как рабити алгиритъмът, в случай, че сте забравили, тук:
https://sortvisualizer.com/mergesort/

**Задача 3**

Да се напише рекурсивна функция, която приема "лабиринт" "лабиринт" (булева матрици от 1ци и 0ли), за която 1цата означава стена, а 0лата път и две цели числа, които да отговарят на координати в лабиринта. Нека функцията върне дали има път от горният ляв ъгъл на матрицата до подадените координатите.