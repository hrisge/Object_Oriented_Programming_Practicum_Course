#include <iostream>
#include <functional>

class Nvector {
    int* arr;
    size_t size;
    void free() {
        delete[] arr;
        size = 0;
    }
    void copy(const Nvector& other) {
        if (other.arr == nullptr) return;
        this->size = other.size;
        arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
    }
public:
    Nvector() {
        arr = nullptr;
        size = 0;
    }
    Nvector(const Nvector& other){
        copy(other);
    }
    Nvector(const int* arr, int size) {
        this->size = size;
        this->arr = new int[size];
        for (int i = 0; i < size; i++) {
            this->arr[i] = arr[i];
        }
    }
    Nvector& operator=(const Nvector& other) {
        if (this == &other) return *this;
        free();
        copy(other);
    }
    ~Nvector() {
        free();
    }

    Nvector& map(const std::function<int(int)>& f) {
        for (int i = 0; i < size; i++) {
            arr[i] = f(arr[i]);
        }
        return *this;
    }

    Nvector& filter(const std::function<bool(int)>& pred) {
        int* result = new int[size];
        int k = 0;
        for (int i = 0; i < size; i++) {
            if (pred(arr[i])) {
                result[k] = arr[i];
                k++;
            }
        }
        delete[] arr;
        arr = result;
        size = k;
        return *this;
    }

    int reduce(const std::function<int(int, int)>& op, int nullValue) {
        int result = nullValue;
        for (int i = 0; i < size; i++) {
            result = op(result, arr[i]);
        }
        return result;
    }
    Nvector& operator+=(const Nvector& other) {
        Nvector temp = *this;
        size += other.size;
        delete[] arr;
        arr = new int[size];
        for (int i = 0; i < temp.size; i++) {
            arr[i] = temp.arr[i];
        }
        for (int i = temp.size; i < size; i++) {
            arr[i] = other.arr[i - temp.size];
        }
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& out, const Nvector& v);
};

std::ostream& operator<<(std::ostream& out, const Nvector& v) {
    for (int i = 0; i < v.size; i++) {
        out << v.arr[i] << " ";
    }
    out << '\n';
    return out;
}


template <class T, class U>
U accumulate(int a, int b, const U& nv,
    const std::function<T(int)>& term,
    const std::function<U(const U&, const T&)>& op) {
    U result = nv;
    for(int i=b; i >= a ; i--){
        result = op(result, term(i));
    }
    return result;
}


int* createArrFromTo(int a, int b) {
    size_t size = b - a + 1;
    int* arr = new int[size];
    return accumulate<int, int*>(a, b, arr, 
        [](int x) {return x; },
        [&size](int* const& result, const int& x)
        {result[--size] = x; return result; });
}



int main()
{
    int arr[5] = { 1,2,3,4,5 };
    Nvector v = Nvector(arr, 5);
    v += v;
    std::cout << v;
    std::cout << v
        .filter([](int x) {return x % 2 == 0; })
        .map([](int x) {return x * x; })
        .reduce([](int x, int y) {return x + y; }, 0);
}
