#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

template<class T>
class ObjectPool {
public:
  T *Allocate();
  T *TryAllocate();

  void Deallocate(T *object);

  ~ObjectPool();

private:
  std::set<T *> allocated;
  std::queue<T *> available;
};

template<class T>
T *ObjectPool<T>::Allocate() {
  if (available.empty()) {
    available.push(new T);
  }
  auto *temp = available.front();
  available.pop();
  allocated.insert(temp);
  return temp;
}

template<class T>
T *ObjectPool<T>::TryAllocate() {
  if (available.empty()) {
    return nullptr;
  }
  auto *temp = available.front();
  available.pop();
  allocated.insert(temp);
  return temp;
}

template<class T>
void ObjectPool<T>::Deallocate(T *object) {
  if (!allocated.count(object)) {
    throw std::invalid_argument("");
  }
  auto it = allocated.find(object);
  available.push(*it);
  allocated.erase(it);
}

template<class T>
ObjectPool<T>::~ObjectPool() {
  for (auto *object : allocated) {
    delete object;
  }
  allocated.clear();

  while (!available.empty()) {
    delete available.front();
    available.pop();
  }
}

void TestObjectPool() {
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

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);

  return 0;
}
