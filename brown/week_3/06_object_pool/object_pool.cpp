#include <list>
#include <queue>
#include <set>
#include <stdexcept>

template <class T>
class ObjectPool {
 public:
  T* Allocate() {
    T* value;
    if (free_.empty()) {
      value = new T();
    } else {
      value = free_.front();
      free_.pop_front();
    }

    current_.insert(value);
    return value;
  }

  T* TryAllocate() {
    if (free_.empty()) {
      return nullptr;
    }
    T* value = free_.front();
    free_.pop_front();
    current_.insert(value);
    return value;
  }

  void Deallocate(T* object) {
    auto it = current_.find(object);
    if (it == current_.end()) {
      throw std::invalid_argument("pointer not in pool");
    }
    current_.erase(it);
    free_.push_back(object);
  }

  ~ObjectPool() {
    for (T* p : current_) {
      delete p;
    }
    for (T* p : free_) {
      delete p;
    }
  }

 private:
  std::list<T*> free_;
  std::set<T*> current_;
};

#if defined(WITH_TESTS)
#  define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#  include <doctest/doctest.h>

TEST_SUITE("Unittest: Object Pool") {
  TEST_CASE("Smoke") {
    ObjectPool<std::string> pool;

    auto* p1 = pool.Allocate();
    auto* p2 = pool.Allocate();
    auto* p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    CHECK_EQ(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    CHECK_EQ(*pool.Allocate(), "third");
    CHECK_EQ(*pool.Allocate(), "first");

    pool.Deallocate(p1);
  }
  TEST_CASE("Smoke2") {
    ObjectPool<std::string> pool;
    std::vector<std::string*> items;
    for (int i = 0; i < 10'000; ++i) {
      items.push_back(pool.Allocate());
    }
    for (int i = 0; i < 10'000; ++i) {
      pool.Deallocate(items.at(static_cast<size_t>(i)));
    }
    for (int i = 0; i < 10'000; ++i) {
      pool.Allocate();
    }
    for (int i = 0; i < 5'000; ++i) {
      pool.Deallocate(items.at(static_cast<size_t>(i)));
    }
  }
}

#endif