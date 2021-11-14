#pragma once

#include <stdexcept>
#include <array>
#include <stdexcept>

template<typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0);

  T &operator[](size_t index);
  const T &operator[](size_t index) const;

  typename std::array<T, N>::iterator begin();
  typename std::array<T, N>::iterator end();
  typename std::array<T, N>::const_iterator begin() const;
  typename std::array<T, N>::const_iterator end() const;

  size_t Size() const;
  size_t Capacity() const;

  void PushBack(const T &value);
  T PopBack();

private:
  std::array<T, N> data;
  size_t size;
};

template<typename T, size_t N>
StackVector<T, N>::StackVector(size_t a_size):size(a_size) {
  if (a_size > N) {
    throw std::invalid_argument("a_size invalid (> N)");
  }
}

template<typename T, size_t N>
T &StackVector<T, N>::operator[](size_t index) {
  return data[index];
}
template<typename T, size_t N>
const T &StackVector<T, N>::operator[](size_t index) const {
  return data[index];
}
template<typename T, size_t N>
typename std::array<T, N>::iterator StackVector<T, N>::begin() {
  return data.begin();
}

template<typename T, size_t N>
typename std::array<T, N>::iterator StackVector<T, N>::end() {
  return data.begin() + size;
}
template<typename T, size_t N>
typename std::array<T, N>::const_iterator StackVector<T, N>::begin() const {
  return data.cbegin();
}
template<typename T, size_t N>
typename std::array<T, N>::const_iterator StackVector<T, N>::end() const {
  return data.cbegin() + size;
}
template<typename T, size_t N>
size_t StackVector<T, N>::Size() const {
  return size;
}
template<typename T, size_t N>
size_t StackVector<T, N>::Capacity() const {
  return N;
}
template<typename T, size_t N>
void StackVector<T, N>::PushBack(const T &value) {
  if (size >= N) {
    throw std::overflow_error("stack overflow");
  }
  data[size++] = value;
}
template<typename T, size_t N>
T StackVector<T, N>::PopBack() {
  if (size == 0U) {
    throw std::underflow_error("stack underflow");
  }

  return data[--size];
}