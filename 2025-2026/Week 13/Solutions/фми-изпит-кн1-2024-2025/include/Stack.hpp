#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>

// Стекът е структура от данни, която работи на принципа
// LIFO(Last In First Out), т. е. последният добавен елемент ще бъде първият изкаран.
// Това ни трябва, за undo операцията във FileSystem, защото искаме да викаме undo
// на командите в ред на най-скорошно извикване(в обратен ред)
// стекът ни предоставя точно такава възможност
// Функционалността на стека може да се симулира и с обикновен вектор, но го правим за удобство
// понеже имплементацията е тривиална
template <class T>
class Stack{
  std::vector<T> vec;

public:
  Stack() = default;

  bool empty() const {
    return vec.empty();
  }

  size_t size() const {
    return vec.size();
  }

  void push(const T& data){
    vec.push_back(data);
  }

  void pop() {
    if(empty()) return;
    vec.pop_back();
  }

  const T& top() const{
    if(empty()) throw std::runtime_error("stack is empty");
    return vec[size() - 1];
  }
};