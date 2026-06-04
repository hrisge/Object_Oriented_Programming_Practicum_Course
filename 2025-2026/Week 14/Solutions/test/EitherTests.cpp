#include "Vector.hpp"
#include "doctest.h"
#include "Either.hpp"
#include <exception>
#include <stdexcept>
#include <string>

TEST_CASE("Either - Create"){
  SUBCASE("Left Value"){
    SUBCASE("Move Value"){
      Either<int, char> a(5);
      REQUIRE(a.is_left());
      CHECK_EQ(a.left(), 5);
    }
    SUBCASE("Copy Value"){
      int num = 5;
      Either<int, char> a(num);
      REQUIRE(a.is_left());
      CHECK_EQ(a.left(), 5);
    }
    
  }
  SUBCASE("Right Value"){
    SUBCASE("Move Value"){
      Either<int, char> a('a');
      REQUIRE(a.is_right());
      CHECK_EQ(a.right(), 'a');
    }
    SUBCASE("Copy Value"){
      char c = 'a';
      Either<int, char> a(c);
      REQUIRE(a.is_right());
      CHECK_EQ(a.right(), 'a');
    } 
  }
}

TEST_CASE("Either - Copy"){
  SUBCASE("Left"){
    Either<int, bool> a(42);
    SUBCASE("Copy Constructor"){
      Either<int, bool> b(a);
      REQUIRE(b.is_left());
      CHECK_EQ(b.left(), 42);
    }
    SUBCASE("Copy operator="){
      Either<int, bool> b(2);
      b = a;
      REQUIRE(b.is_left());
      CHECK_EQ(b.left(), 42);
    }
  }
  SUBCASE("Right Value"){
    Either<int, bool> a(true);
    SUBCASE("Copy Constructor"){
      Either<int, bool> b(a);
      REQUIRE(b.is_right());
      CHECK_EQ(b.right(), true);
    }
    SUBCASE("Copy operator="){
      Either<int, bool> b(2);
      b = a;
      REQUIRE(b.is_right());
      CHECK_EQ(b.right(), true);
    }
  }
}

TEST_CASE("Either - Move"){
  SUBCASE("Left Value"){
    Either<int, bool> a(42);
    SUBCASE("Move Constructor"){
      Either<int, bool> b(std::move(a));
      REQUIRE(b.is_left());
      CHECK_EQ(b.left(), 42);
    }
    SUBCASE("Move operator="){
      Either<int, bool> b(2);
      b = std::move(a);
      REQUIRE(b.is_left());
      CHECK_EQ(b.left(), 42);
    }
  }
  SUBCASE("Right Value"){
    Either<int, bool> a(true);
    SUBCASE("Move Constructor"){
      Either<int, bool> b(std::move(a));
      REQUIRE(b.is_right());
      CHECK_EQ(b.right(), true);
    }
    SUBCASE("Move operator="){
      Either<int, bool> b(2);
      b = std::move(a);
      REQUIRE(b.is_right());
      CHECK_EQ(b.right(), true);
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

TEST_CASE("Either - left"){
  Vector<int> vec({1,2,3,4,5});
  Either<Vector<int>, bool> either(vec);
  CHECK_EQ(vec, either.left());
  CHECK_NOTHROW(either.left()[0] = 2);
  CHECK_EQ(either.left()[0], 2);

  Vector<int> vec2(std::move(either).left());
  CHECK(either.left().empty());
}

TEST_CASE("Either - right"){
  Vector<int> vec({1,2,3,4,5});
  Either<bool, Vector<int>> either(vec);
  CHECK_EQ(vec, either.right());
  CHECK_NOTHROW(either.right()[0] = 2);
  CHECK_EQ(either.right()[0], 2);

  Vector<int> vec2(std::move(either).right());
  CHECK(either.right().empty());
}

TEST_CASE("Either - and_then"){
  Either<int, bool> either(5);
  SUBCASE("Left Value"){

  }
  SUBCASE("Right Value"){
    either = false;
  }

  Either<double, bool> result = either.and_then<double>([](int n){return Either<double, bool>(n/2.0);});

  if(either.is_left()){
    CHECK_EQ(result.left(), either.left()/2.0);
  }
  else{
    CHECK_FALSE(result.right());
  }
}

TEST_CASE("Either - transform_left"){
  Either<int, bool> either(11);
  SUBCASE("Left Value"){

  }
  SUBCASE("Right Value"){
    either = true;
  }

  Either<double, bool> result = either.transform_left<double>([](int n){return n/2.0;});
  if(either.is_left()){
    CHECK_EQ(result.left(), either.left()/2.0);
  }
  else{
    CHECK(result.right());
  }
}

TEST_CASE("Either - transform_right"){
  Either<bool, int> either(11);
  SUBCASE("Left Value"){
    either = true;
  }
  SUBCASE("Right Value"){
    
  }

  Either<bool, double> result = either.transform_right<double>([](int n){return n/2.0;});
  if(!either.is_left()){
    CHECK_EQ(result.right(), either.right()/2.0);
  }
  else{
    CHECK(result.left());
  }
}


int functionThatCanThrow(int n){
  if(n%2 == 0) return n/2;
  else throw std::runtime_error("n is not divisible by 2");
}

Either<int, std::runtime_error> divideBy2IfEven(int n){
  try{
    return functionThatCanThrow(n);
  }
  catch(const std::runtime_error& e){
    return e;
  }
}

TEST_CASE("Either Example"){
  Vector<int> nums;

  for(int i = 0; i < 10; i++){
    Either<int, std::string> result =
     divideBy2IfEven(i)
    .and_then<int>([](int n){return n+1;})
    .visit<int, std::string>([&nums](int n){nums.push_back(n); return n;},
                             [](const std::exception& e){return e.what();});
    
    if(result.is_left()){
      CHECK_EQ(result.left(), i/2 + 1);
    }
    else{
      CHECK_EQ(result.right(), "n is not divisible by 2");
    }
  }
  CHECK_EQ(nums, Vector<int>({1,2,3,4, 5}));
}
