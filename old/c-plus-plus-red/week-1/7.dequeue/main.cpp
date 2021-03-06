#include "deque.hpp"
#include "test_runner.h"

void TestT1() {
  Deque<int> d;
  ASSERT_EQUAL(d.Empty(), true);
  ASSERT_EQUAL(d.Size(), 0u);
}

void TestT2() {
  Deque<int> d;
  d.PushBack(1);
  d.PushFront(2);
  ASSERT_EQUAL(d.Size(), 2u);
  ASSERT_EQUAL(d.Empty(), false);
  ASSERT_EQUAL(d[0], 2);
  ASSERT_EQUAL(d[1], 1);
  ASSERT_EQUAL(d.At(0), 2);
  ASSERT_EQUAL(d.At(1), 1);
  d.PushFront(3);
  ASSERT_EQUAL(d[0], 3);
  ASSERT_EQUAL(d.At(0), 3);
  d.Back() = 999;
  ASSERT_EQUAL(d[2], 999);
  d.Front() = 100;
  ASSERT_EQUAL(d[0], 100);
}

void TestT3() {
  Deque<int> d;
  d.Front();
  d.Back();

//  d.PushBack(1);
//  d.PushBack(2);
//  d.PushBack(3);
//  d.PushBack(4);
//  d.PushBack(5);
  d.PushFront(99);
  d.PushFront(98);
//  auto a = d.At(1);
//  auto a = d[4];
  auto a = d.Front();
  auto b = d.Back();

//  d.PushFront(1);
//  d.Front();
//  d.Back();

}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestT1);
  RUN_TEST(tr, TestT2);
  RUN_TEST(tr, TestT3);

  return 0;
}