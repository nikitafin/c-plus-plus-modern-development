#pragma once

#include <algorithm>
#include <cstdlib>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector();
  explicit SimpleVector(std::size_t size);
  SimpleVector &operator=(const SimpleVector &other);
  ~SimpleVector();

  T &operator[](std::size_t index);

  T *begin();
  T *end();

  const T *cbegin() const;
  const T *cend() const;

  [[nodiscard]] std::size_t Size() const;
  [[nodiscard]] std::size_t Capacity() const;
  void PushBack(const T &value);

private:
  T *data;
  std::size_t size;
  std::size_t capacity;
};

template <typename T>
SimpleVector<T>::SimpleVector() : data(nullptr), size(0U), capacity(0U) {}
template <typename T>
SimpleVector<T>::SimpleVector(std::size_t size)
    : data(new T[size]), size(size), capacity(size) {}
template <typename T>
SimpleVector<T> &
SimpleVector<T>::operator=(const SimpleVector<T> &other) {
  //  if (other == this) {
  //    return *this;
  //  }
  delete[] data;
  data     = new T[other.capacity];
  size     = other.size;
  capacity = other.capacity;
  std::copy(other.cbegin(), other.cend(), begin());

  return *this;
}
template <typename T>
SimpleVector<T>::~SimpleVector() {
  delete[] data;
}
template <typename T>
T &
SimpleVector<T>::operator[](std::size_t index) {
  return data[index];
}
template <typename T>
T *
SimpleVector<T>::begin() {
  return data;
}
template <typename T>
T *
SimpleVector<T>::end() {
  return data + size;
}
template <typename T>
const T *
SimpleVector<T>::cbegin() const {
  return data;
}
template <typename T>
const T *
SimpleVector<T>::cend() const {
  return data + size;
}
template <typename T>
std::size_t
SimpleVector<T>::Size() const {
  return size;
}
template <typename T>
std::size_t
SimpleVector<T>::Capacity() const {
  return capacity;
}
template <typename T>
void
SimpleVector<T>::PushBack(const T &value) {
  if (size == capacity) {
    capacity    = (capacity == 0) ? 1 : capacity * 2;
    T *new_data = new T[capacity];
    if (data != nullptr) {
      std::copy(data, data + size, new_data);
    }
    delete[] data;
    data = new_data;
  }

  data[size] = value;
  size++;
}
