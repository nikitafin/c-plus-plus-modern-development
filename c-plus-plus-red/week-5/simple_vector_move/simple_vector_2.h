#pragma once
#include <algorithm>
#include <cstdint>

// Реализуйте SimpleVector в этом файле
// и отправьте его на проверку

template<typename T>
class SimpleVector {
public:
  SimpleVector() = default;
  explicit SimpleVector(size_t size);
  ~SimpleVector();

  T& operator[](size_t index);

  T *begin();
  T *end();

  [[nodiscard]] size_t Size() const;
  [[nodiscard]] size_t Capacity() const;

  void PushBack(const T& value);
  void PushBack(T&& value);
  // При необходимости перегрузите
  // существующие публичные методы

private:
  T* data{ nullptr };
  std::size_t size{ 0U };
  std::size_t capacity{ 0U };
};

template<typename T>
SimpleVector<T>::SimpleVector(size_t size)
  : data{ new T[size] }
  , size{ size }
  , capacity{ size }
{}

template<typename T>
SimpleVector<T>::~SimpleVector()
{
  delete[] data;
}

template<typename T>
T&
SimpleVector<T>::operator[](std::size_t index)
{
  return data[index];
}

template<typename T>
T*
SimpleVector<T>::begin()
{
  return data;
}
template<typename T>
T*
SimpleVector<T>::end()
{
  return data + size;
}

template<typename T>
std::size_t
SimpleVector<T>::Size() const
{
  return size;
}

template<typename T>
std::size_t
SimpleVector<T>::Capacity() const
{
  return capacity;
}

template<typename T>
void
SimpleVector<T>::PushBack(const T& value)
{
  if (size == capacity) {
    capacity = (capacity == 0) ? 1 : capacity * 2;
    T* new_data = new T[capacity];
    if (data != nullptr) {
      std::copy(data, data + size, new_data);
    }
    delete[] data;
    data = new_data;
  }

  data[size] = value;
  size++;
}

template<typename T>
void
SimpleVector<T>::PushBack(T&& value)
{
  if (size == capacity) {
    capacity = (capacity == 0) ? 1 : capacity * 2;
    T* new_data = new T[capacity];
    if (data != nullptr) {
      std::move(data, data + size, new_data);
    }
    delete[] data;
    data = new_data;
  }

  data[size] = std::move(value);
  size++;
}
