#pragma once
#include <stdexcept>
#include <vector>

template <typename Type>
class Deque {
public:
  Deque();
  bool Empty() const;
  size_t Size() const;
  Type &operator[](size_t index);
  const Type &operator[](size_t index) const;
  Type &At(size_t index);
  const Type &At(size_t index) const;
  Type &Front();
  const Type &Front() const;
  Type &Back();
  const Type &Back() const;
  void PushFront(Type element);
  void PushBack(Type element);

private:
  std::vector<Type> front;
  std::vector<Type> back;
};

template <typename Type>
Deque<Type>::Deque() : front(), back() {}

template <typename Type>
bool
Deque<Type>::Empty() const {
  return front.empty() and back.empty();
}

template <typename Type>
size_t
Deque<Type>::Size() const {
  return front.size() + back.size();
}

template <typename Type>
Type &
Deque<Type>::operator[](size_t index) {
  if (index < front.size()) {
    return front[front.size() - index - 1];
  }
  return back[index - front.size()];
}

template <typename Type>
const Type &
Deque<Type>::operator[](size_t index) const {
  if (index < front.size()) {
    return front[front.size() - index - 1];
  }
  return back[index - front.size()];
}

template <typename Type>
Type &
Deque<Type>::At(size_t index) {
  if (index < front.size()) {
    return front.at(front.size() - index - 1);
  }
  return back.at(index - front.size());
}

template <typename Type>
const Type &
Deque<Type>::At(size_t index) const {
  if (index < front.size()) {
    return front.at(front.size() - index - 1);
  }
  return back.at(index - front.size());
}

template <typename Type>
Type &
Deque<Type>::Front() {
  if (!front.empty()) {
    return front.back();
  }
  return back.front();
}

template <typename Type>
const Type &
Deque<Type>::Front() const {
  if (!front.empty()) {
    return front.back();
  }
  return back.front();
}

template <typename Type>
Type &
Deque<Type>::Back() {
  if (!back.empty()) {
    return back.back();
  }
  return front.front();
}

template <typename Type>
const Type &
Deque<Type>::Back() const {
  if (!back.empty()) {
    return back.back();
  }
  return front.front();
}

template <typename Type>
void
Deque<Type>::PushFront(Type element) {
  front.push_back(element);
}

template <typename Type>
void
Deque<Type>::PushBack(Type element) {
  back.push_back(element);
}
