#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <stdexcept>
#include <string>

template<class T>
class ObjectPool {
public:
  T *Allocate();

  T *TryAllocate();

  void Deallocate(T *object);

  ~ObjectPool();

private:
  std::set<T *> allocated;
  std::queue<T *> released;
};

template<class T>
T *
ObjectPool<T>::Allocate() {
  if (released.empty()) {
    T *n = new T();
    allocated.insert(n);
    return n;
  }

  T *n = released.front();
  released.pop();

  allocated.insert(n);
  return n;
}

template<class T>
T *
ObjectPool<T>::TryAllocate() {
  if (released.empty()) {
    return nullptr;
  }

  T *n = released.front();
  released.pop();

  allocated.insert(n);
  return n;
}

template<class T>
void
ObjectPool<T>::Deallocate(T *object) {
  auto it = allocated.find(object);
  if (it == allocated.end()) {
    throw std::invalid_argument("");
  }
  T *obj = *it;
  allocated.erase(it);
  released.push(obj);
}

template<class T>
ObjectPool<T>::~ObjectPool() {
  for (T *t: allocated) {
    delete t;
  }
  allocated.clear();

  while (!released.empty()) {
    T *obj = released.front();
    delete obj;
    released.pop();
  }
}

void
TestObjectPool() {
  ObjectPool<std::string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int
main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
