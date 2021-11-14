#include "test_runner.h"

#include <vector>

template<typename T>
class LinkedList {
public:
  struct Node {
    T value;
    Node *next = nullptr;
  };

  ~LinkedList();

  void PushFront(const T &value);
  void InsertAfter(Node *node, const T &value);
  void RemoveAfter(Node *node);
  void PopFront();

  Node *GetHead() { return head; }
  const Node *GetHead() const { return head; }

private:
  Node *head = nullptr;
};
template<typename T>
LinkedList<T>::~LinkedList() {
  while (head != nullptr) {
    Node *c = head;
    head = head->next;
    delete c;
  }
}
template<typename T>
void LinkedList<T>::PushFront(const T &value) {
  Node *new_head = new Node{value, head};
  head = new_head;
}
template<typename T>
void LinkedList<T>::InsertAfter(LinkedList::Node *node, const T &value) {
  if (node == nullptr) {
    PushFront(value);
  } else {
    Node *new_node = new Node{value, node->next};
    node->next = new_node;
  }
}
template<typename T>
void LinkedList<T>::RemoveAfter(LinkedList::Node *node) {
  if (node == nullptr) {
    PopFront();
  } else {
    if (node->next == nullptr) {
      return;
    }
    Node *temp = node->next;
    node->next = node->next->next;
    delete temp;
  }
}
template<typename T>
void LinkedList<T>::PopFront() {
  if (head == nullptr) {
    return;
  }
  Node *temp_node = head->next;
  delete head;
  head = temp_node;
}

template<typename T>
std::vector<T> ToVector(const LinkedList<T> &list) {
  std::vector<T> result;
  for (auto node = list.GetHead(); node; node = node->next) {
    result.push_back(node->value);
  }
  return result;
}

void TestPushFront() {
  LinkedList<int> list;

  list.PushFront(1);
  ASSERT_EQUAL(list.GetHead()->value, 1);
  list.PushFront(2);
  ASSERT_EQUAL(list.GetHead()->value, 2);
  list.PushFront(3);
  ASSERT_EQUAL(list.GetHead()->value, 3);

  const std::vector<int> expected = {3, 2, 1};
  ASSERT_EQUAL(ToVector(list), expected);
}

void TestInsertAfter() {
  LinkedList<std::string> list;

  list.PushFront("a");
  auto head = list.GetHead();
  ASSERT(head);
  ASSERT_EQUAL(head->value, "a");

  list.InsertAfter(head, "b");
  const std::vector<std::string> expected1 = {"a", "b"};
  ASSERT_EQUAL(ToVector(list), expected1);

  list.InsertAfter(head, "c");
  const std::vector<std::string> expected2 = {"a", "c", "b"};
  ASSERT_EQUAL(ToVector(list), expected2);
}

void TestRemoveAfter() {
  LinkedList<int> list;
  for (int i = 1; i <= 5; ++i) {
    list.PushFront(i);
  }

  const std::vector<int> expected = {5, 4, 3, 2, 1};
  ASSERT_EQUAL(ToVector(list), expected);

  auto next_to_head = list.GetHead()->next;
  list.RemoveAfter(next_to_head); // удаляем 3
  list.RemoveAfter(next_to_head); // удаляем 2

  const std::vector<int> expected1 = {5, 4, 1};
  ASSERT_EQUAL(ToVector(list), expected1);

  while (list.GetHead()->next) {
    list.RemoveAfter(list.GetHead());
  }
  ASSERT_EQUAL(list.GetHead()->value, 5);
}

void TestPopFront() {
  LinkedList<int> list;

  for (int i = 1; i <= 5; ++i) {
    list.PushFront(i);
  }
  for (int i = 1; i <= 5; ++i) {
    list.PopFront();
  }
  ASSERT(list.GetHead() == nullptr);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestPushFront);
  RUN_TEST(tr, TestInsertAfter);
  RUN_TEST(tr, TestRemoveAfter);
  RUN_TEST(tr, TestPopFront);
  return 0;
}
