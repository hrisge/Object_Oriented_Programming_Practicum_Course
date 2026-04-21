// tests.cpp - Comprehensive tests for Array, Delivery, Product, Item, Market, ShoppingCart, User
// Compile: g++ -std=c++17 tests.cpp -o tests && ./tests

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <cstring>

// ---- Minimal test framework ----
static int passed = 0;
static int failed = 0;

#define TEST(name) void name()
#define RUN(name) do { \
    try { name(); std::cout << "[PASS] " #name "\n"; passed++; } \
    catch (const std::exception& e) { std::cout << "[FAIL] " #name " -> " << e.what() << "\n"; failed++; } \
    catch (...) { std::cout << "[FAIL] " #name " -> unknown exception\n"; failed++; } \
} while(0)

#define ASSERT(cond) do { if (!(cond)) throw std::runtime_error("Assertion failed: " #cond); } while(0)
#define ASSERT_EQ(a, b) do { if (!((a) == (b))) throw std::runtime_error("Expected equal: " #a " == " #b); } while(0)
#define ASSERT_THROWS(expr) do { bool threw = false; try { expr; } catch (...) { threw = true; } if (!threw) throw std::runtime_error("Expected exception for: " #expr); } while(0)

// ---- Inline implementations (header-only style) ----
// We re-include source by copying the relevant headers inline.
// In a real project you'd just link the .o files.

#pragma warning(disable : 4996)
#include "Sort.hpp"
#include "Array.hpp"
#include "Delivery.hpp"
#include "Product.hpp"
#include "Item.hpp"
#include "Market.hpp"
#include "ShoppingCart.hpp"
#include "User.hpp"

// ==================== Array Tests ====================

TEST(Array_DefaultConstructor) {
    Array<int> a;
    ASSERT(a.empty());
    ASSERT_EQ(a.size(), (size_t)0);
}

TEST(Array_PushBack) {
    Array<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    ASSERT_EQ(a.size(), (size_t)3);
    ASSERT_EQ(a[0], 1);
    ASSERT_EQ(a[1], 2);
    ASSERT_EQ(a[2], 3);
}

TEST(Array_PopBack) {
    Array<int> a;
    a.push_back(10);
    a.push_back(20);
    a.pop_back();
    ASSERT_EQ(a.size(), (size_t)1);
    ASSERT_EQ(a[0], 10);
}

TEST(Array_CopyConstructor) {
    Array<int> a;
    a.push_back(5);
    a.push_back(6);
    Array<int> b(a);
    ASSERT_EQ(b.size(), (size_t)2);
    ASSERT_EQ(b[0], 5);
    ASSERT_EQ(b[1], 6);
    // Deep copy: modifying b doesn't affect a
    b[0] = 99;
    ASSERT_EQ(a[0], 5);
}

TEST(Array_AssignmentOperator) {
    Array<int> a;
    a.push_back(1);
    Array<int> b;
    b = a;
    ASSERT_EQ(b.size(), (size_t)1);
    ASSERT_EQ(b[0], 1);
}

TEST(Array_Iterator) {
    Array<int> a;
    a.push_back(10);
    a.push_back(20);
    a.push_back(30);
    int sum = 0;
    for (int x : a) sum += x;
    ASSERT_EQ(sum, 60);
}

TEST(Array_ConstIterator) {
    Array<int> a;
    a.push_back(1);
    a.push_back(2);
    const Array<int>& ca = a;
    int sum = 0;
    for (const int& x : ca) sum += x;
    ASSERT_EQ(sum, 3);
}

TEST(Array_Filter) {
    Array<int> a;
    for (int i = 1; i <= 6; i++) a.push_back(i);
    Array<int> evens = a.filter([](const int& x) { return x % 2 == 0; });
    ASSERT_EQ(evens.size(), (size_t)3);
    ASSERT_EQ(evens[0], 2);
    ASSERT_EQ(evens[1], 4);
    ASSERT_EQ(evens[2], 6);
}

TEST(Array_Map) {
    Array<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    Array<int> doubled = a.map<int>([](const int& x) { return x * 2; });
    ASSERT_EQ(doubled[0], 2);
    ASSERT_EQ(doubled[1], 4);
    ASSERT_EQ(doubled[2], 6);
}

TEST(Array_SortBy_Comparator) {
    Array<int> a;
    a.push_back(3);
    a.push_back(1);
    a.push_back(2);
    Array<int> sorted = a.sortBy([](const int& x, const int& y) { return x < y; });
    ASSERT_EQ(sorted[0], 1);
    ASSERT_EQ(sorted[1], 2);
    ASSERT_EQ(sorted[2], 3);
}

TEST(Array_SortBy_Descending) {
    Array<int> a;
    a.push_back(3);
    a.push_back(1);
    a.push_back(2);
    Array<int> sorted = a.sortBy([](const int& x, const int& y) { return x > y; });
    ASSERT_EQ(sorted[0], 3);
    ASSERT_EQ(sorted[1], 2);
    ASSERT_EQ(sorted[2], 1);
}

TEST(Array_SortBy_Property) {
    Array<int> a;
    a.push_back(3);
    a.push_back(1);
    a.push_back(2);
    Array<int> sorted = a.sortBy<int>([](const int& x) { return x; });
    ASSERT_EQ(sorted[0], 1);
    ASSERT_EQ(sorted[1], 2);
    ASSERT_EQ(sorted[2], 3);
}

TEST(Array_Reverse) {
    Array<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    Array<int> r = a.reverse();
    ASSERT_EQ(r[0], 3);
    ASSERT_EQ(r[1], 2);
    ASSERT_EQ(r[2], 1);
}

TEST(Array_RemoveFirst) {
    Array<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(2);
    a.remove_first([](const int& x) { return x == 2; });
    ASSERT_EQ(a.size(), (size_t)3);
    ASSERT_EQ(a[0], 1);
    ASSERT_EQ(a[1], 3);
    ASSERT_EQ(a[2], 2); // second 2 should still be there
}

TEST(Array_RemoveFirst_NoMatch) {
    Array<int> a;
    a.push_back(1);
    a.push_back(2);
    a.remove_first([](const int& x) { return x == 99; });
    ASSERT_EQ(a.size(), (size_t)2); // unchanged
}

TEST(Array_Find) {
    Array<int> a;
    a.push_back(10);
    a.push_back(20);
    ASSERT_EQ(a.find([](const int& x) { return x == 20; }), 20);
}

TEST(Array_Find_Throws) {
    Array<int> a;
    a.push_back(1);
    ASSERT_THROWS(a.find([](const int& x) { return x == 99; }));
}

TEST(Array_FindPos) {
    Array<int> a;
    a.push_back(5);
    a.push_back(10);
    auto it = a.findPos([](const int& x) { return x == 10; });
    ASSERT(it.isValid());
    ASSERT_EQ(*it, 10);
}

TEST(Array_FindPos_NotFound) {
    Array<int> a;
    a.push_back(5);
    auto it = a.findPos([](const int& x) { return x == 99; });
    ASSERT(!it.isValid());
}

TEST(Array_Max) {
    Array<int> a;
    a.push_back(1);
    a.push_back(5);
    a.push_back(3);
    ASSERT_EQ(a.max<int>([](const int& x) { return x; }), 5);
}

TEST(Array_Min) {
    Array<int> a;
    a.push_back(4);
    a.push_back(1);
    a.push_back(3);
    ASSERT_EQ(a.min<int>([](const int& x) { return x; }), 1);
}

TEST(Array_Max_EmptyThrows) {
    Array<int> a;
    ASSERT_THROWS(a.max<int>([](const int& x) { return x; }));
}

TEST(Array_Min_EmptyThrows) {
    Array<int> a;
    ASSERT_THROWS(a.min<int>([](const int& x) { return x; }));
}

TEST(Array_LargeGrowth) {
    Array<int> a;
    for (int i = 0; i < 1000; i++) a.push_back(i);
    ASSERT_EQ(a.size(), (size_t)1000);
    ASSERT_EQ(a[999], 999);
}

// ==================== Delivery Tests ====================

TEST(Delivery_Constructor) {
    Delivery d("Express", 2);
    ASSERT_EQ(strcmp(d.getName(), "Express"), 0);
    ASSERT_EQ(d.getDeliveryTime(), 2);
}

TEST(Delivery_DefaultConstructor) {
    Delivery d;
    ASSERT_EQ(d.getDeliveryTime(), 0);
}

TEST(Delivery_Equality) {
    Delivery a("Fast", 1);
    Delivery b("Fast", 1);
    Delivery c("Slow", 5);
    ASSERT(a == b);
    ASSERT(!(a == c));
}

// ==================== Product Tests ====================

static Product makeProduct(const char* name, double price, int deliveryDays, Category cat = GROCERY) {
    return Product(name, { 1,1,1 }, 0.5, price, Delivery("Standard", deliveryDays), cat);
}

TEST(Product_Constructor) {
    Product p = makeProduct("Apple", 1.5, 3);
    ASSERT_EQ(strcmp(p.getName(), "Apple"), 0);
    ASSERT_EQ(p.getPrice(), 1.5);
    ASSERT_EQ(p.getDelivery().getDeliveryTime(), 3);
    ASSERT_EQ(p.getCategory(), GROCERY);
}

TEST(Product_Equality) {
    Product a = makeProduct("Apple", 1.5, 3);
    Product b = makeProduct("Apple", 1.5, 3);
    Product c = makeProduct("Orange", 2.0, 3);
    ASSERT(a == b);
    ASSERT(!(a == c));
}

TEST(Product_DefaultConstructor) {
    Product p;
    ASSERT_EQ(p.getCategory(), _SIZE);
}

// ==================== Market Tests ====================

TEST(Market_AddAndGetProduct) {
    Market m;
    Product p = makeProduct("Milk", 2.0, 1);
    m.addProduct(p);
    ASSERT_EQ(m.getItems().size(), (size_t)1);
    ASSERT(m.getItems()[0].getProduct() == p);
}

TEST(Market_RemoveProduct) {
    Market m;
    Product p = makeProduct("Milk", 2.0, 1);
    m.addProduct(p);
    m.removeProduct(p);
    ASSERT(m.getItems().empty());
}

TEST(Market_BuyProduct) {
    Market m;
    Product p = makeProduct("Milk", 2.0, 1);
    m.addProduct(p);
    m.buyProduct(p, 10);
    ASSERT_EQ(m.getItems()[0].getCount(), (size_t)10);
}

TEST(Market_SellProduct) {
    Market m;
    Product p = makeProduct("Milk", 2.0, 1);
    m.addProduct(p);
    m.buyProduct(p, 10);
    m.sellProduct(p, 3);
    ASSERT_EQ(m.getItems()[0].getCount(), (size_t)7);
}

TEST(Market_BuyProduct_NotListed) {
    Market m;
    Product p = makeProduct("Ghost", 5.0, 1);
    ASSERT_THROWS(m.buyProduct(p, 1));
}

TEST(Market_SellProduct_NotListed) {
    Market m;
    Product p = makeProduct("Ghost", 5.0, 1);
    ASSERT_THROWS(m.sellProduct(p, 1));
}

TEST(Market_ReceivingTime_InStock) {
    Market m;
    Product p = makeProduct("Milk", 2.0, 3);
    m.addProduct(p);
    m.buyProduct(p, 10);
    // Requesting <= stock -> 0 wait time
    ASSERT_EQ(m.receivingTimeFor(p, 5), 0);
}

TEST(Market_ReceivingTime_OutOfStock) {
    Market m;
    Product p = makeProduct("Milk", 2.0, 3);
    m.addProduct(p);
    m.buyProduct(p, 2);
    // Requesting more than stock -> delivery time
    ASSERT_EQ(m.receivingTimeFor(p, 10), 3);
}

TEST(Market_ReceivingTime_NotListed) {
    Market m;
    Product p = makeProduct("Ghost", 1.0, 1);
    ASSERT_THROWS(m.receivingTimeFor(p, 1));
}

TEST(Market_MultipleProducts) {
    Market m;
    Product p1 = makeProduct("Bread", 1.0, 1);
    Product p2 = makeProduct("Butter", 3.0, 2);
    m.addProduct(p1);
    m.addProduct(p2);
    ASSERT_EQ(m.getItems().size(), (size_t)2);
    m.removeProduct(p1);
    ASSERT_EQ(m.getItems().size(), (size_t)1);
    ASSERT(m.getItems()[0].getProduct() == p2);
}

// ==================== ShoppingCart Tests ====================

TEST(ShoppingCart_AddProduct) {
    Market m;
    Product p = makeProduct("Bread", 1.0, 1);
    m.addProduct(p);
    m.buyProduct(p, 5);

    ShoppingCart cart("MyCart", m);
    cart.addProduct(p);
    ASSERT_EQ(cart.getCount(), (size_t)1);
}

TEST(ShoppingCart_AddProduct_NotInMarket) {
    Market m;
    Product p = makeProduct("Ghost", 1.0, 1);
    ShoppingCart cart("MyCart", m);
    ASSERT_THROWS(cart.addProduct(p));
}

TEST(ShoppingCart_AddSameProductTwice) {
    Market m;
    Product p = makeProduct("Egg", 0.5, 1);
    m.addProduct(p);
    m.buyProduct(p, 10);

    ShoppingCart cart("MyCart", m);
    cart.addProduct(p);
    cart.addProduct(p);
    ASSERT_EQ(cart.getCount(), (size_t)2);
}

TEST(ShoppingCart_RemoveProduct) {
    Market m;
    Product p = makeProduct("Milk", 1.5, 2);
    m.addProduct(p);
    m.buyProduct(p, 5);

    ShoppingCart cart("MyCart", m);
    cart.addProduct(p);
    cart.removeProduct(p);
    ASSERT_EQ(cart.getCount(), (size_t)0);
}

TEST(ShoppingCart_GetPrice) {
    Market m;
    Product p1 = makeProduct("A", 3.0, 1);
    Product p2 = makeProduct("B", 7.0, 1);
    m.addProduct(p1);
    m.addProduct(p2);
    m.buyProduct(p1, 5);
    m.buyProduct(p2, 5);

    ShoppingCart cart("Cart", m);
    cart.addProduct(p1);
    cart.addProduct(p2);
    // getPrice sums product prices (one of each)
    ASSERT_EQ(cart.getPrice(), 10.0);
}

TEST(ShoppingCart_GetDeliveryTime) {
    Market m;
    Product p1 = makeProduct("Fast", 1.0, 1);
    Product p2 = makeProduct("Slow", 2.0, 5);
    m.addProduct(p1);
    m.addProduct(p2);
    m.buyProduct(p1, 5);
    m.buyProduct(p2, 5);

    ShoppingCart cart("Cart", m);
    cart.addProduct(p1);
    cart.addProduct(p2);
    ASSERT_EQ(cart.getDeliveryTime(), 5);
}

TEST(ShoppingCart_AddCount) {
    Market m;
    Product p = makeProduct("Rice", 2.0, 3);
    m.addProduct(p);
    m.buyProduct(p, 10);

    ShoppingCart cart("Cart", m);
    cart.addProduct(p);  // count=1
    cart.addCount(p, 4); // count=5
    ASSERT_EQ(cart.getCount(), (size_t)5);
}

TEST(ShoppingCart_LowerCount) {
    Market m;
    Product p = makeProduct("Rice", 2.0, 3);
    m.addProduct(p);
    m.buyProduct(p, 10);

    ShoppingCart cart("Cart", m);
    cart.addProduct(p);
    cart.addCount(p, 4); // count=5
    cart.lowerCount(p, 2); // count=3
    ASSERT_EQ(cart.getCount(), (size_t)3);
}

TEST(ShoppingCart_LowerCount_TooMuch) {
    Market m;
    Product p = makeProduct("Rice", 2.0, 3);
    m.addProduct(p);
    m.buyProduct(p, 10);

    ShoppingCart cart("Cart", m);
    cart.addProduct(p); // count=1
    ASSERT_THROWS(cart.lowerCount(p, 5));
}

TEST(ShoppingCart_FindByName) {
    Market m;
    Product p = makeProduct("Sugar", 1.0, 2);
    m.addProduct(p);
    m.buyProduct(p, 5);

    ShoppingCart cart("Cart", m);
    cart.addProduct(p);
    ASSERT_EQ(strcmp(cart.findByName("Sugar").getProduct().getName(), "Sugar"), 0);
}

TEST(ShoppingCart_MaxByPrice) {
    Market m;
    Product p1 = makeProduct("Cheap", 1.0, 1);
    Product p2 = makeProduct("Expensive", 9.0, 1);
    m.addProduct(p1);
    m.addProduct(p2);
    m.buyProduct(p1, 5);
    m.buyProduct(p2, 5);

    ShoppingCart cart("Cart", m);
    cart.addProduct(p1);
    cart.addProduct(p2);
    ASSERT_EQ(cart.maxByPrice().getProduct().getPrice(), 9.0);
}

TEST(ShoppingCart_MinByPrice) {
    Market m;
    Product p1 = makeProduct("Cheap", 1.0, 1);
    Product p2 = makeProduct("Expensive", 9.0, 1);
    m.addProduct(p1);
    m.addProduct(p2);
    m.buyProduct(p1, 5);
    m.buyProduct(p2, 5);

    ShoppingCart cart("Cart", m);
    cart.addProduct(p1);
    cart.addProduct(p2);
    ASSERT_EQ(cart.minByPrice().getProduct().getPrice(), 1.0);
}

TEST(ShoppingCart_SortByPrice) {
    Market m;
    Product p1 = makeProduct("Expensive", 9.0, 1);
    Product p2 = makeProduct("Cheap", 1.0, 1);
    Product p3 = makeProduct("Mid", 5.0, 1);
    m.addProduct(p1); m.addProduct(p2); m.addProduct(p3);
    m.buyProduct(p1, 5); m.buyProduct(p2, 5); m.buyProduct(p3, 5);

    ShoppingCart cart("Cart", m);
    cart.addProduct(p1);
    cart.addProduct(p2);
    cart.addProduct(p3);
    cart.sortByPrice();
    ASSERT_EQ(cart.findByName("Cheap").getProduct().getPrice(), 1.0);
    // First item should be cheapest after sort
}

TEST(ShoppingCart_FilterByCategory) {
    Market m;
    Product p1 = makeProduct("Apple", 1.0, 1, GROCERY);
    Product p2("Laptop", { 30,20,5 }, 2.0, 999.0, Delivery("Express", 3), TECHNOLOGY);
    m.addProduct(p1);
    m.addProduct(p2);
    m.buyProduct(p1, 5);
    m.buyProduct(p2, 5);

    ShoppingCart cart("Cart", m);
    cart.addProduct(p1);
    cart.addProduct(p2);
    ShoppingCart groceries = cart.filterByCategory(GROCERY);
    ASSERT_EQ(groceries.getCount(), (size_t)1);
}

TEST(ShoppingCart_FilterByPriceRange) {
    Market m;
    Product p1 = makeProduct("Cheap", 1.0, 1);
    Product p2 = makeProduct("Mid", 5.0, 1);
    Product p3 = makeProduct("Pricey", 20.0, 1);
    m.addProduct(p1); m.addProduct(p2); m.addProduct(p3);
    m.buyProduct(p1, 5); m.buyProduct(p2, 5); m.buyProduct(p3, 5);

    ShoppingCart cart("Cart", m);
    cart.addProduct(p1); cart.addProduct(p2); cart.addProduct(p3);
    ShoppingCart filtered = cart.filterByPriceRange(2.0, 15.0);
    ASSERT_EQ(filtered.getCount(), (size_t)1); // only mid
}

TEST(ShoppingCart_FilterByDeliveryTimeRange) {
    Market m;
    Product p1 = makeProduct("Fast", 1.0, 1);
    Product p2 = makeProduct("Medium", 1.0, 3);
    Product p3 = makeProduct("Slow", 1.0, 7);
    m.addProduct(p1); m.addProduct(p2); m.addProduct(p3);
    m.buyProduct(p1, 5); m.buyProduct(p2, 5); m.buyProduct(p3, 5);

    ShoppingCart cart("Cart", m);
    cart.addProduct(p1); cart.addProduct(p2); cart.addProduct(p3);
    ShoppingCart filtered = cart.filterByDeliveryTimeRange(2, 5);
    ASSERT_EQ(filtered.getCount(), (size_t)1); // only medium
}

TEST(ShoppingCart_Clear) {
    Market m;
    Product p = makeProduct("Sugar", 1.0, 2);
    m.addProduct(p);
    m.buyProduct(p, 5);

    ShoppingCart cart("Cart", m);
    cart.addProduct(p);
    cart.clear();
    ASSERT_EQ(cart.getCount(), (size_t)0);
}

TEST(ShoppingCart_SetName) {
    Market m;
    ShoppingCart cart("OldName", m);
    cart.setName("NewName");
    ASSERT_EQ(strcmp(cart.getName(), "NewName"), 0);
}

// ==================== User Tests ====================

TEST(User_AddCart) {
    Market m;
    User u("Alice", 1000.0, m);
    u.addCart("Groceries");
    ShoppingCart& cart = u.find([](const ShoppingCart& c) {
        return strcmp(c.getName(), "Groceries") == 0;
        });
    ASSERT_EQ(strcmp(cart.getName(), "Groceries"), 0);
}

TEST(User_RenameCart) {
    Market m;
    User u("Bob", 500.0, m);
    u.addCart("OldName");
    ShoppingCart& cart = u.find([](const ShoppingCart& c) { return true; });
    u.renameCart(cart, "NewName");
    ASSERT_EQ(strcmp(cart.getName(), "NewName"), 0);
}

TEST(User_AddToAllCarts) {
    Market m;
    Product p = makeProduct("Banana", 0.5, 1);
    m.addProduct(p);
    m.buyProduct(p, 20);

    User u("Carol", 200.0, m);
    u.addCart("Cart1");
    u.addCart("Cart2");
    u.addToAllCarts(p);

    ShoppingCart& c1 = u.find([](const ShoppingCart& c) {
        return strcmp(c.getName(), "Cart1") == 0;
        });
    ShoppingCart& c2 = u.find([](const ShoppingCart& c) {
        return strcmp(c.getName(), "Cart2") == 0;
        });
    ASSERT_EQ(c1.getCount(), (size_t)1);
    ASSERT_EQ(c2.getCount(), (size_t)1);
}

TEST(User_MaxByPrice) {
    Market m;
    Product cheap = makeProduct("Cheap", 1.0, 1);
    Product pricey = makeProduct("Pricey", 100.0, 1);
    m.addProduct(cheap); m.addProduct(pricey);
    m.buyProduct(cheap, 10); m.buyProduct(pricey, 10);

    User u("Dave", 500.0, m);
    u.addCart("Small");
    u.addCart("Big");
    u.find([](const ShoppingCart& c) { return strcmp(c.getName(), "Small") == 0; }).addProduct(cheap);
    u.find([](const ShoppingCart& c) { return strcmp(c.getName(), "Big") == 0; }).addProduct(pricey);

    ASSERT_EQ(u.maxByPrice().getPrice(), 100.0);
    ASSERT_EQ(u.minByPrice().getPrice(), 1.0);
}

TEST(User_FilterByPriceRange) {
    Market m;
    Product cheap = makeProduct("Cheap", 1.0, 1);
    Product pricey = makeProduct("Pricey", 50.0, 1);
    m.addProduct(cheap); m.addProduct(pricey);
    m.buyProduct(cheap, 10); m.buyProduct(pricey, 10);

    User u("Eve", 500.0, m);
    u.addCart("SmallCart");
    u.addCart("BigCart");
    u.find([](const ShoppingCart& c) { return strcmp(c.getName(), "SmallCart") == 0; }).addProduct(cheap);
    u.find([](const ShoppingCart& c) { return strcmp(c.getName(), "BigCart") == 0; }).addProduct(pricey);

    u.filterByPriceRange(0.0, 10.0);
    // Only SmallCart should remain
    ShoppingCart& remaining = u.find([](const ShoppingCart& c) {
        return strcmp(c.getName(), "SmallCart") == 0;
        });
    ASSERT_EQ(remaining.getPrice(), 1.0);
}

TEST(User_SortByPrice) {
    Market m;
    Product p1 = makeProduct("P1", 10.0, 1);
    Product p2 = makeProduct("P2", 5.0, 1);
    Product p3 = makeProduct("P3", 20.0, 1);
    m.addProduct(p1); m.addProduct(p2); m.addProduct(p3);
    m.buyProduct(p1, 5); m.buyProduct(p2, 5); m.buyProduct(p3, 5);

    User u("Frank", 1000.0, m);
    u.addCart("C1"); u.addCart("C2"); u.addCart("C3");
    u.find([](const ShoppingCart& c) { return strcmp(c.getName(), "C1") == 0; }).addProduct(p1);
    u.find([](const ShoppingCart& c) { return strcmp(c.getName(), "C2") == 0; }).addProduct(p2);
    u.find([](const ShoppingCart& c) { return strcmp(c.getName(), "C3") == 0; }).addProduct(p3);

    u.sortByPrice();
    ASSERT_EQ(u.minByPrice().getPrice(), 5.0);
    ASSERT_EQ(u.maxByPrice().getPrice(), 20.0);
}

TEST(User_MaxProductByPrice) {
    Market m;
    Product cheap = makeProduct("Cheap", 1.0, 1);
    Product pricey = makeProduct("Pricey", 50.0, 1);
    m.addProduct(cheap); m.addProduct(pricey);
    m.buyProduct(cheap, 10); m.buyProduct(pricey, 10);

    User u("Grace", 500.0, m);
    u.addCart("C1"); u.addCart("C2");
    u.find([](const ShoppingCart& c) { return strcmp(c.getName(), "C1") == 0; }).addProduct(cheap);
    u.find([](const ShoppingCart& c) { return strcmp(c.getName(), "C2") == 0; }).addProduct(pricey);

    ASSERT_EQ(u.maxProductByPrice().getPrice(), 50.0);
    ASSERT_EQ(u.minProductByPrice().getPrice(), 1.0);
}

// ==================== Sort Tests ====================

TEST(Sort_QuickSortInts) {
    int arr[] = { 5, 3, 8, 1, 9, 2 };
    quickSort<int*, int>(arr, arr + 6, [](int a, int b) { return a < b; });
    ASSERT_EQ(arr[0], 1);
    ASSERT_EQ(arr[1], 2);
    ASSERT_EQ(arr[2], 3);
    ASSERT_EQ(arr[3], 5);
    ASSERT_EQ(arr[4], 8);
    ASSERT_EQ(arr[5], 9);
}

TEST(Sort_QuickSortSingleElement) {
    int arr[] = { 42 };
    quickSort<int*, int>(arr, arr + 1, [](int a, int b) { return a < b; });
    ASSERT_EQ(arr[0], 42);
}

TEST(Sort_QuickSortAlreadySorted) {
    int arr[] = { 1, 2, 3, 4, 5 };
    quickSort<int*, int>(arr, arr + 5, [](int a, int b) { return a < b; });
    for (int i = 0; i < 5; i++) ASSERT_EQ(arr[i], i + 1);
}

TEST(Sort_QuickSortReversed) {
    int arr[] = { 5, 4, 3, 2, 1 };
    quickSort<int*, int>(arr, arr + 5, [](int a, int b) { return a < b; });
    for (int i = 0; i < 5; i++) ASSERT_EQ(arr[i], i + 1);
}

// ==================== Main ====================

int main() {
    std::cout << "=== Array Tests ===\n";
    RUN(Array_DefaultConstructor);
    RUN(Array_PushBack);
    RUN(Array_PopBack);
    RUN(Array_CopyConstructor);
    RUN(Array_AssignmentOperator);
    RUN(Array_Iterator);
    RUN(Array_ConstIterator);
    RUN(Array_Filter);
    RUN(Array_Map);
    RUN(Array_SortBy_Comparator);
    RUN(Array_SortBy_Descending);
    RUN(Array_SortBy_Property);
    RUN(Array_Reverse);
    RUN(Array_RemoveFirst);
    RUN(Array_RemoveFirst_NoMatch);
    RUN(Array_Find);
    RUN(Array_Find_Throws);
    RUN(Array_FindPos);
    RUN(Array_FindPos_NotFound);
    RUN(Array_Max);
    RUN(Array_Min);
    RUN(Array_Max_EmptyThrows);
    RUN(Array_Min_EmptyThrows);
    RUN(Array_LargeGrowth);

    std::cout << "\n=== Delivery Tests ===\n";
    RUN(Delivery_Constructor);
    RUN(Delivery_DefaultConstructor);
    RUN(Delivery_Equality);

    std::cout << "\n=== Product Tests ===\n";
    RUN(Product_Constructor);
    RUN(Product_Equality);
    RUN(Product_DefaultConstructor);

    std::cout << "\n=== Market Tests ===\n";
    RUN(Market_AddAndGetProduct);
    RUN(Market_RemoveProduct);
    RUN(Market_BuyProduct);
    RUN(Market_SellProduct);
    RUN(Market_BuyProduct_NotListed);
    RUN(Market_SellProduct_NotListed);
    RUN(Market_ReceivingTime_InStock);
    RUN(Market_ReceivingTime_OutOfStock);
    RUN(Market_ReceivingTime_NotListed);
    RUN(Market_MultipleProducts);

    std::cout << "\n=== ShoppingCart Tests ===\n";
    RUN(ShoppingCart_AddProduct);
    RUN(ShoppingCart_AddProduct_NotInMarket);
    RUN(ShoppingCart_AddSameProductTwice);
    RUN(ShoppingCart_RemoveProduct);
    RUN(ShoppingCart_GetPrice);
    RUN(ShoppingCart_GetDeliveryTime);
    RUN(ShoppingCart_AddCount);
    RUN(ShoppingCart_LowerCount);
    RUN(ShoppingCart_LowerCount_TooMuch);
    RUN(ShoppingCart_FindByName);
    RUN(ShoppingCart_MaxByPrice);
    RUN(ShoppingCart_MinByPrice);
    RUN(ShoppingCart_SortByPrice);
    RUN(ShoppingCart_FilterByCategory);
    RUN(ShoppingCart_FilterByPriceRange);
    RUN(ShoppingCart_FilterByDeliveryTimeRange);
    RUN(ShoppingCart_Clear);
    RUN(ShoppingCart_SetName);

    std::cout << "\n=== User Tests ===\n";
    RUN(User_AddCart);
    RUN(User_RenameCart);
    RUN(User_AddToAllCarts);
    RUN(User_MaxByPrice);
    RUN(User_FilterByPriceRange);
    RUN(User_SortByPrice);
    RUN(User_MaxProductByPrice);

    std::cout << "\n=== Sort Tests ===\n";
    RUN(Sort_QuickSortInts);
    RUN(Sort_QuickSortSingleElement);
    RUN(Sort_QuickSortAlreadySorted);
    RUN(Sort_QuickSortReversed);

    std::cout << "\n============================\n";
    std::cout << "Results: " << passed << " passed, " << failed << " failed\n";


        Market market;

        Product apple("Apple", { 1,1,1 }, 0.2, 1.99, Delivery("Standard", 2), GROCERY);
        Product laptop("Laptop", { 35,25,3 }, 2.5, 999.99, Delivery("Express", 1), TECHNOLOGY);
        Product banana("Banana", { 2,1,1 }, 0.15, 0.99, Delivery("Standard", 3), GROCERY);

        market.addProduct(apple);
        market.addProduct(laptop);
        market.addProduct(banana);


        market.buyProduct(apple, 50);
        market.buyProduct(laptop, 5);
        market.buyProduct(banana, 100);


        User user("Alice", 1500.0, market);


        user.addCart("Groceries");
        user.addCart("Electronics");

        ShoppingCart& groceries = user.find([](const ShoppingCart& c) {
            return strcmp(c.getName(), "Groceries") == 0;
            });
        ShoppingCart& electronics = user.find([](const ShoppingCart& c) {
            return strcmp(c.getName(), "Electronics") == 0;
            });

        groceries.addProduct(apple);
        groceries.addProduct(banana);
        groceries.addCount(apple, 2);   // 3
        electronics.addProduct(laptop);

   
        std::cout << "Groceries cart price: $" << groceries.getPrice() << "\n"; // 6.96
        std::cout << "Groceries delivery time: " << groceries.getDeliveryTime() << " days\n"; // 3
        std::cout << "Most expensive product in groceries: "
            << groceries.maxByPrice().getProduct().getName() << " ($" // Apple
            << groceries.maxByPrice().getProduct().getPrice() << ")\n"; //1.99

 
        ShoppingCart onlyGroceries = groceries.filterByCategory(GROCERY);
        std::cout << "Filtered groceries (only GROCERY): " << onlyGroceries.getCount() << " items\n"; //4

        electronics.sortByPrice();
        std::cout << "Electronics sorted, cheapest product: "
            << electronics.minByPrice().getProduct().getName() << "\n"; // Laptop

        std::cout << "\nUser's most expensive product across all carts: "
            << user.maxProductByPrice().getName() << " ($" // Laptop
            << user.maxProductByPrice().getPrice() << ")\n"; // 999.99

        std::cout << "User's cheapest product across all carts: "
            << user.minProductByPrice().getName() << " ($" // Banana
            << user.minProductByPrice().getPrice() << ")\n"; // 0.99

        user.filterByPriceRange(10.0, 1000.0); 

        user.sortByPrice();
        std::cout << "Carts sorted by price, cheapest cart total: $"
            << user.minByPrice().getPrice() << "\n"; // 999.99

        return 0;
}