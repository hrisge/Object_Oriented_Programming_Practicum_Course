
#include "doctest.h"
#include "Vector.hpp"

TEST_CASE("Vector - Create"){
  Vector<int> v;
  CHECK(v.empty());
  CHECK_EQ(v.size(), 0);
  CHECK_EQ(v.capacity(), 0);
}

TEST_CASE("Vector - Push Back"){
  Vector<int> v;
  SUBCASE("Move"){
    v.push_back(2);
    CHECK_FALSE(v.empty());
    CHECK_EQ(v.size(), 1);
    CHECK_GE(v.capacity(), 1);
    v.push_back(3);
    CHECK_EQ(v.size(), 2);
    CHECK_GE(v.capacity(), 2);
  }
  SUBCASE("Copy"){
    int a = 1;
    int b = 2;
    v.push_back(a);
    CHECK_FALSE(v.empty());
    CHECK_EQ(v.size(), 1);
    CHECK_GE(v.capacity(), 1);
    v.push_back(b);
    CHECK_EQ(v.size(), 2);
    CHECK_GE(v.capacity(), 2);
  }
  for(int i = 0; i < 10; i++)
    v.push_back(i);
  CHECK_EQ(v.size(), 12);
  CHECK_GE(v.capacity(), 12);
}

TEST_CASE("Vector - operator[]"){
  Vector<int> v;
  for(int i = 0;i < 10; i++){
    v.push_back(i);
  }
  for(int i = 0; i < 10; i++){
    CHECK_EQ(v[i], i);
  }
  SUBCASE("const operator[]"){
    const Vector<int>& v2 = v;
    for(int i = 0; i < 10; i++){
      CHECK_EQ(v2[i], i);
    }
  }
}

TEST_CASE("Vector - Copy"){
  Vector<int> v;
  for(int i = 1; i < 4; i++){
    v.push_back(i);
  }
  SUBCASE("Copy Constructor"){
    Vector<int> copy(v);
    CHECK_EQ(v.capacity(),copy.capacity());
    CHECK_EQ(v.size(), copy.size());
    for(int i = 0; i < v.size(); i++){
      CHECK_EQ(v[i], copy[i]);
      v[i]++;
    }
    for(int i = 0; i < v.size(); i++){
      CHECK_NE(v[i], copy[i]);
    }
  }
  SUBCASE("Copy operator="){
    Vector<int> copy;
    copy = v;
    CHECK_EQ(v.capacity(),copy.capacity());
    CHECK_EQ(v.size(), copy.size());
    for(int i = 0; i < v.size(); i++){
      CHECK_EQ(v[i], copy[i]);
      v[i]++;
    }
    for(int i = 0; i < v.size(); i++){
      CHECK_NE(v[i], copy[i]);
    }
  }

}

TEST_CASE("Vector - Move"){
  Vector<int> v;
  for(int i = 1; i < 4; i++){
    v.push_back(i);
  }
  Vector<int> vCopy(v);
  SUBCASE("Move Constructor"){
    Vector<int> copy(std::move(v));
    CHECK_EQ(vCopy.capacity(),copy.capacity());
    CHECK_EQ(vCopy.size(), copy.size());
    for(int i = 0; i < vCopy.size(); i++){
      CHECK_EQ(vCopy[i], copy[i]);
    }
    CHECK(v.empty());
  }
  SUBCASE("Move operator="){
    Vector<int> copy;
    copy = std::move(v);
    CHECK_EQ(vCopy.capacity(),copy.capacity());
    CHECK_EQ(vCopy.size(), copy.size());
    for(int i = 0; i < vCopy.size(); i++){
      CHECK_EQ(vCopy[i], copy[i]);
    }
    CHECK(v.empty());
  }
}