#pragma once

#include <functional>
#include <utility>

template <class Left, class Right>
class Either {
  Left* leftValue;
  Right* rightValue;
  bool isLeft;

  void copy(const Either &other);

  void move(Either &&other) noexcept;

  void free();

public:
  Either(const Left &left);
  Either(const Right &right);

  Either(Left &&left);
  Either(Right &&right);

  Either(const Either &other);
  Either(Either &&other) noexcept;
  Either &operator=(const Either &other);
  Either &operator=(Either &&other) noexcept;

  bool is_left() const;
  bool is_right() const;

  Left &left() &;
  const Left &left() const&;
  Left&& left() &&;

  Right &right() &;
  const Right &right() const&;
  Right &&right() &&;

  template <class U>
  Either<U, Right> transform_left(const std::function<U(const Left &)> &f) const;

  template <class U>
  Either<Left, U> transform_right(const std::function<U(const Right &)> &f) const;

  template <class U>
  Either<U, Right> and_then(const std::function<Either<U, Right>(const Left &)> &f) const;

  template <class U, class V>
  Either<U, V> visit(const std::function<U(const Left &)> &left,
                     const std::function<V(const Right &)> &right);
};

template <class Left, class Right>
template <class U, class V>
Either<U, V> Either<Left, Right>::visit(const std::function<U(const Left &)> &left, const std::function<V(const Right &)> &right) {
  if (is_left())
    return left(this->left());
  else
    return right(this->right());
}

template <class Left, class Right>
template <class U>
Either<U, Right> Either<Left, Right>::and_then(const std::function<Either<U, Right>(const Left &)> &f) const {
  if (is_left())
    return f(left());
  else
    return Either<U, Right>(right());
}

template <class Left, class Right>
template <class U>
Either<Left, U> Either<Left, Right>::transform_right(const std::function<U(const Right &)> &f) const {
  if (is_left())
    return Either<Left, U>(left());
  else
    return Either<Left, U>(f(right()));
}

template <class Left, class Right>
template <class U>
Either<U, Right> Either<Left, Right>::transform_left(const std::function<U(const Left &)> &f) const {
  if (is_left())
    return Either<U, Right>(f(left()));
  else
    return Either<U, Right>(right());
}

template <class Left, class Right>
void Either<Left, Right>::copy(const Either &other) {
  isLeft = other.isLeft;
  if (isLeft) {
    leftValue = new Left(other.left());
    rightValue = nullptr;
  } 
  else {
    rightValue = new Right(other.right());
    leftValue = nullptr;
  }
}
template <class Left, class Right>
void Either<Left, Right>::move(Either &&other) noexcept{
  std::swap(isLeft, other.isLeft);
  std::swap(leftValue, other.leftValue);
  std::swap(rightValue, other.rightValue);
}
template <class Left, class Right> void Either<Left, Right>::free() {
  if (isLeft) {
    delete leftValue;
  } 
  else {
    delete rightValue;
  }
}
template <class Left, class Right>
Either<Left, Right>::Either(const Left &left)
    : leftValue(new Left(left)), rightValue(nullptr), isLeft(true) {}

template <class Left, class Right>
Either<Left, Right>::Either(const Right &right)
    : leftValue(nullptr), rightValue(new Right(right)), isLeft(false) {}

template <class Left, class Right>
Either<Left, Right>::Either(Left &&left)
    : leftValue(new Left(std::move(left))), rightValue(nullptr), isLeft(true) {}

template <class Left, class Right>
Either<Left, Right>::Either(Right &&right)
    : leftValue(nullptr), rightValue(new Right(std::move(right))), isLeft(false) {}

template <class Left, class Right>
Either<Left, Right>::Either(const Either &other) {
  copy(other);
}

template <class Left, class Right>
Either<Left, Right>::Either(Either &&other) noexcept {
  move(std::move(other));
}

template <class Left, class Right>
Either<Left, Right> &Either<Left, Right>::operator=(const Either &other) {
  if (this != &other) {
    free();
    copy(other);
  }
  return *this;
}
template <class Left, class Right>
Either<Left, Right> &Either<Left, Right>::operator=(Either &&other) noexcept {
  if (this != &other) {
    free();
    move(std::move(other));
  }
  return *this;
}

template <class Left, class Right>
bool Either<Left, Right>::is_left() const {
  return isLeft;
}

template <class Left, class Right>
bool Either<Left, Right>::is_right() const {
  return !isLeft;
}

template <class Left, class Right>
const Left &Either<Left, Right>::left() const& {
  return *leftValue;
}

template <class Left, class Right>
Left &Either<Left, Right>::left() &{
  return *leftValue;
}

template <class Left, class Right>
const Right &Either<Left, Right>::right() const& {
  return *rightValue;
}

template <class Left, class Right> 
Right &Either<Left, Right>::right() &{
  return *rightValue;
}

template <class Left, class Right>
Left &&Either<Left, Right>::left() &&{
  return std::move(*leftValue);
}

template <class Left, class Right> 
Right &&Either<Left, Right>::right() &&{
  return std::move(*rightValue);
}
