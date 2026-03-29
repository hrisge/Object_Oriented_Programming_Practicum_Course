#include "Nvector.hpp"

void Nvector::copy(const Nvector& other)
{
    n = other.n;
    arr = new int[n];
    for (size_t i = 0; i < n; i++) {
        arr[i] = other.arr[i];
    }
}

void Nvector::free()
{
    delete[] arr;
}

Nvector::Nvector() : arr(nullptr), n(0) {}

void Nvector::concat(const Nvector& other)
{
    int* newArr = new int[n + other.n] {0};
    for (size_t i = 0; i < n; i++) {
        newArr[i] = arr[i];
    }
    for (size_t i = 0; i < other.n; i++) {
        newArr[n + i] = other[i];
    }
    delete[] arr;
    arr = newArr;
    n += other.n;
}

Nvector::Nvector(const int* arr, size_t n) : n(n)
{
    this->arr = new int[n];
    for (size_t i = 0; i < n; i++) {
        this->arr[i] = arr[i];
    }
}

Nvector::Nvector(size_t n) : arr(new int[n] {0}), n(n) {}

Nvector::Nvector(const Nvector& other) 
{
    copy(other);
}

Nvector& Nvector::operator=(const Nvector& other)
{
    if (this == &other) return *this;
    free();
    copy(other);
    return *this;
}

Nvector::~Nvector()
{
    free();
}

Nvector Nvector::operator+(const Nvector& other) const
{
    Nvector result(std::max(n, other.n));
    size_t i = 0;
    while (i < n && i < other.n) {
        result[i] = arr[i] + other[i];
        i++;
    }
    while (i < n) {
        result[i] = arr[i];
        i++;
    }
    while (i < other.n) {
        result[i] = other[i];
        i++;
    }
    return result;
}

Nvector Nvector::operator-(const Nvector& other) const
{
    Nvector result(std::max(n, other.n));
    size_t i = 0;
    while (i < n && i < other.n) {
        result[i] = arr[i] - other[i];
        i++;
    }
    while (i < n) {
        result[i] = arr[i];
        i++;
    }
    while (i < other.n) {
        result[i] = -other[i];
        i++;
    }
    return result;
}

Nvector Nvector::operator*(int scalar) const
{
    Nvector result(*this);
    for (size_t i = 0; i < n; i++) {
        result[i] *= scalar;
    }
    return result;
}

size_t Nvector::size() const
{
    return n;
}

int& Nvector::operator[](size_t ind)
{
    return arr[ind];
}

const int& Nvector::operator[](size_t ind) const
{
    return arr[ind];
}

Nvector Nvector::concatMap(std::function<Nvector(int)> f)
{
    Nvector result;
    for (size_t i = 0; i < n; i++) {
        result.concat(f(arr[i]));
    }
    return result;
}

std::ostream& operator<<(std::ostream& out, const Nvector& vec)
{
    for (size_t i = 0; i < vec.n; i++) {
        out << vec[i] << " ";
    }
    return out;
}

std::istream& operator>>(std::istream& in, Nvector& vec)
{
    vec.free();
    vec.arr = new int[0];
    vec.n = 0;
    int input;
    int arr[1];
    do{
        in >> input;
        arr[0] = input;
        vec.concat(Nvector(arr, 1));
    } while (in && in.peek() != '\n');
    return in;
}
