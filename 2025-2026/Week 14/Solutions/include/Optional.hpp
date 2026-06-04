#pragma once
#include <functional>
#include <utility>

template<class T>
class Optional{
    T* data;
    bool empty;

    void copy(const Optional &other);

    void move(Optional &&other) noexcept;

    void free();

  public:
    Optional();
    Optional(const T &data);
    Optional(T &&data);
    Optional(const Optional &other);
    Optional(Optional &&other) noexcept;
    Optional &operator=(const Optional &other);
    Optional &operator=(Optional &&other) noexcept;
    ~Optional();

    bool has_value() const;

    T &value() &;
    const T &value() const&;
    T &&value() &&;
    

    
    T &operator*() &;
    const T &operator*() const&;
    T &&operator*() &&;

    const T *operator->() const;
    T *operator->();

    T value_or(const T &fallback) const;

    Optional<T> or_else(const std::function<Optional<T>()> &fallback) const;

    template <class U>
    Optional<U> and_then(const std::function<Optional<U>(const T &)> &f) const;

    template <class U>
    Optional<U> transform(const std::function<U(const T &)> &f) const;
};

template <class T>
template <class U>
Optional<U> Optional<T>::transform(const std::function<U(const T &)> &f) const {
  if (has_value())
    return Optional<U>(f(value()));
  else
    return Optional<U>();
}

template <class T>
template <class U>
Optional<U> Optional<T>::and_then(const std::function<Optional<U>(const T &)> &f) const {
  if (has_value())
    return f(value());
  else
    return Optional<U>();
}

template <class T>
void Optional<T>::copy(const Optional &other) {
  if (other.has_value()) {
    empty = false;
    data = new T(other.value());
  } else {
    empty = true;
    data = nullptr;
  }
}

template <class T> 
void Optional<T>::move(Optional &&other) noexcept {
  data = other.data;
  empty = other.empty;

  other.data = nullptr;
  other.empty = true;
}
template <class T> 
void Optional<T>::free() {
  delete data;
  empty = true;
}

template <class T>
Optional<T>::Optional() : data(nullptr), empty(true) {}

template <class T>
Optional<T>::Optional(const T &data) : data(new T(data)), empty(false) {}

template <class T>
Optional<T>::Optional(T &&data) : data(new T(std::move(data))), empty(false) {}

template <class T> 
Optional<T>::Optional(const Optional &other) {
  copy(other);
}

template <class T> 
Optional<T>::Optional(Optional &&other) noexcept {
  move(std::move(other));
}

template <class T>
Optional<T> &Optional<T>::operator=(const Optional &other) {
  if (this == &other)
    return *this;
  free();
  copy(other);
  return *this;
}

template <class T> 
Optional<T>& Optional<T>::operator=(Optional &&other) noexcept {
  if (this == &other)
    return *this;
  free();
  move(std::move(other));
  return *this;
}

template <class T> 
Optional<T>::~Optional() { free(); }

template <class T> 
bool Optional<T>::has_value() const { return !empty; }

template <class T>
const T &Optional<T>::value() const& { return *data; }

template <class T> 
T &Optional<T>::value() & { return *data; }

template <class T> 
T &&Optional<T>::value() && { return std::move(*data); }

template <class T>
const T &Optional<T>::operator*() const& {
  return value();
}

template <class T> 
T &Optional<T>::operator*() & {
   return value();
}

template <class T> 
T &&Optional<T>::operator*() && {
   return std::move(value());
}

template <class T>
const T *Optional<T>::operator->() const {
  return data;
}

template <class T>
T *Optional<T>::operator->() { return data; }

template <class T>
T Optional<T>::value_or(const T &fallback) const {
  if (has_value())
    return value();
  else
    return fallback;
}

template <class T>
Optional<T> Optional<T>::or_else(const std::function<Optional<T>()> &fallback) const {
  if (has_value())
    return *this;
  else
    return fallback();
};
