
#include "Optional.hpp"
#include "Vector.hpp"
#include "doctest.h"
#include <cstring>
#include <vector>

TEST_CASE("Optional - Create"){
  SUBCASE("Empty"){
    Optional<int> a;
    CHECK_FALSE(a.has_value());
  }
  SUBCASE("With Value"){
    SUBCASE("Move Value"){
      Optional<int> a(2);
      REQUIRE(a.has_value());
      CHECK_EQ(a.value(), 2);
    }
    SUBCASE("Copy Value"){
      int num = 2;
      Optional<int> a(num);
      REQUIRE(a.has_value());
      CHECK_EQ(a.value(), 2);
    } 
  }
}

TEST_CASE("Optional - Copy"){
  SUBCASE("Empty"){
    Optional<int> a;
    SUBCASE("Copy Constructor"){
      Optional<int> b(a);
      CHECK_FALSE(b.has_value());
    }
    SUBCASE("Copy operator="){
      Optional<int> b(2);
      b = a;
      CHECK_FALSE(b.has_value());
    }
  }
  SUBCASE("With Value"){
    Optional<int> a(42);
    SUBCASE("Copy Constructor"){
      Optional<int> b(a);
      REQUIRE(b.has_value());
      CHECK_EQ(b.value(), 42);
    }
    SUBCASE("Copy operator="){
      Optional<int> b(2);
      b = a;
      REQUIRE(b.has_value());
      CHECK_EQ(b.value(), 42);
    }
  }
}

TEST_CASE("Optional - Move"){
  SUBCASE("Empty"){
    Optional<int> a;
    SUBCASE("Move Constructor"){
      Optional<int> b(std::move(a));
      CHECK_FALSE(b.has_value());
      CHECK_FALSE(a.has_value());
    }
    SUBCASE("Move operator="){
      Optional<int> b(2);
      b = std::move(a);
      CHECK_FALSE(b.has_value());
      CHECK_FALSE(a.has_value());
    }
  }
  SUBCASE("With Value"){
    Optional<int> a(42);
    SUBCASE("Move Constructor"){
      Optional<int> b(std::move(a));
      REQUIRE(b.has_value());
      CHECK_EQ(b.value(), 42);
      CHECK_FALSE(a.has_value());
    }
    SUBCASE("Move operator="){
      Optional<int> b(2);
      b = std::move(a);
      REQUIRE(b.has_value());
      CHECK_EQ(b.value(), 42);
      CHECK_FALSE(a.has_value());
    }
  }
}
template <class T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs){
  if(lhs.size() != rhs.size()) return false;
  for(size_t i = 0; i < lhs.size(); i++){
    if(lhs[i]!=rhs[i]) return false;
  }
  return true;
}

TEST_CASE("Optional - value"){
  Vector<int> vec({1,2,3,4,5});
  Optional<Vector<int>> optional(vec);
  CHECK_EQ(vec, optional.value());
  CHECK_NOTHROW(optional.value()[0] = 2);
  CHECK_EQ(optional.value()[0], 2);

  Vector<int> vec2(std::move(optional).value());
  CHECK(optional.value().empty());
}

TEST_CASE("Optional - value_or"){
  Optional<int> optional;
  int expected;
  int fallback = 5;
  SUBCASE("Empty"){
    expected = fallback;
  }
  SUBCASE("With Value"){
    optional = 10;
    expected = 10;
  }
  CHECK_NOTHROW(optional.value_or(fallback));
  CHECK_EQ(optional.value_or(fallback), expected);
}

TEST_CASE("Optional - or_else"){
  std::function<Optional<int>()> zero = [](){return Optional<int>(0);};
  SUBCASE("Empty"){
    Optional<int> optional;
    CHECK_EQ(optional.or_else(zero).value(), 0);
  }
  SUBCASE("With Value"){
    Optional<int> optional(5);
    CHECK_EQ(optional.or_else(zero).value(), 5);
  }
}

TEST_CASE("Optional - and_then"){
  Optional<int> optional;
  SUBCASE("Empty"){

  }
  SUBCASE("With Value"){
    optional = 11;
  }

  Optional<double> result = optional.and_then<double>([](int n){return Optional<double>(n/2.0);});
  if(optional.has_value()){
    CHECK_EQ(result.value(), optional.value()/2.0);
  }
  else{
    CHECK_FALSE(result.has_value());
  }
}

TEST_CASE("Optional - transform"){
  Optional<int> optional;
  SUBCASE("Empty"){

  }
  SUBCASE("With Value"){
    optional = 11;
  }

  Optional<double> result = optional.transform<double>([](int n){return n/2.0;});
  if(optional.has_value()){
    CHECK_EQ(result.value(), optional.value()/2.0);
  }
  else{
    CHECK_FALSE(result.has_value());
  }
}

template <class T>
class Reference{
  T* ptr;
public:
  Reference(T& ref) : ptr(&ref) {}
  operator T&() {return *ptr;}
  operator T&() const {return *ptr;}
};

template <class T>
Optional<Reference<T>> dereference(T* ptr){
  if(!ptr) return {};
  else return Optional<Reference<T>>(*ptr);
}

TEST_CASE("Optional Example"){
  std::vector<int*> v;
  for(int i = 0; i < 10; i++){
    if(i % 9 == 0){
      v.push_back(nullptr);
    }
    else {
      v.push_back(new int(i));
    }
  }

  int sum = 0;

  for(int i = 0; i < v.size(); i++){
    int oldValue;

    sum += 
      dereference(v[i])
      .and_then<int>([&oldValue](int& a){
        oldValue = a;
        a *= a;
        return Optional<int>(a);
      }).or_else([](){
        return Optional<int>(9);
      }).value();

    if(v[i]){
      CHECK_EQ(*v[i], oldValue * oldValue);
      delete v[i];
    }
  }

  CHECK_EQ(sum, 222);

}