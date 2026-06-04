#pragma once

#include <cstddef>
#include <utility>
#include <vector>

template<class T>
class Vector {
  T* arr;
  size_t m_size;
  size_t m_capacity;

  void free(){
    delete arr;
    m_size = 0;
    m_capacity = 0;
  }

  void copy(const Vector& other){
    arr = new T[other.m_capacity];
    m_capacity = other.m_capacity;
    m_size = other.m_size;

    for(size_t i = 0 ; i < m_size; i++){
      arr[i] = other.arr[i];
    }
  }

  void move(Vector&& other) noexcept {
    arr = other.arr;
    m_size = other.m_size;
    m_capacity = other.m_capacity;

    other.arr = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
  }

  void resize() {
    if(m_capacity == 0) m_capacity = 2;
    m_capacity *= 2;
    T* newArr = new T[m_capacity];
    for(int i = 0; i < m_size ; i++){
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
  }

public:
  Vector() : arr(nullptr), m_size(0), m_capacity(0) {}
  Vector(const std::vector<T>& vec) : Vector(){
    for(const T& el : vec){
      push_back(el);
    }
  }
  Vector(const Vector& other) {
    copy(other);
  }
  Vector(Vector&& other) noexcept{
    move(std::move(other));
  }
  Vector& operator=(const Vector& other) {
    if(this != &other){
      free();
      copy(other);
    }
    return *this;
  }
  Vector& operator=(Vector&& other) noexcept {
    if(this != &other){
      free();
      move(std::move(other));
    }
    return *this;
  }
  ~Vector(){
    free();
  }

  bool empty() const {
    return m_size == 0;
  }

  size_t size() const {
    return m_size;
  }

  size_t capacity() const {
    return m_capacity;
  }

  T& operator[](size_t index) {
    return arr[index];
  }
  
  const T& operator[](size_t index) const {
    return arr[index];
  }

  void push_back(const T& el){
    if(m_size >= m_capacity){
      resize();
    }
    arr[m_size++] = el;
  }

  void push_back(T&& el) {
    if(m_size >= m_capacity){
      resize();
    }
    arr[m_size++] = std::move(el);
  }

};
