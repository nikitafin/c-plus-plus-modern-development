#pragma once

#include <cstdint>
#include <cstdlib>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector
{
public:
    SimpleVector();
    explicit SimpleVector(size_t size);
    ~SimpleVector();

    T & operator[](size_t index);

    T * begin();
    T * end();

    size_t Size() const;
    size_t Capacity() const;
    void PushBack(const T & value);

private:
    T * data;
    size_t size;
    size_t capacity;
};

template <typename T>
SimpleVector<T>::SimpleVector() : data{nullptr}, size{0}, capacity{0}
{
}

template <typename T>
SimpleVector<T>::SimpleVector(size_t size) : data{new T[size]}, size{size}, capacity{size}
{
}

template <typename T>
SimpleVector<T>::~SimpleVector()
{
    delete[] data;
}

template <typename T>
T & SimpleVector<T>::operator[](size_t index)
{
    return data[index];
}

template <typename T>
T * SimpleVector<T>::begin()
{
    return data;
}

template <typename T>
T * SimpleVector<T>::end()
{
    return data + size;
}

template <typename T>
size_t SimpleVector<T>::Size() const
{
    return size;
}

template <typename T>
size_t SimpleVector<T>::Capacity() const
{
    return capacity;
}

template <typename T>
void SimpleVector<T>::PushBack(const T & value)
{
    if (size == 0)
    {
        capacity = 1;
        data = new T[1];
    }
    if (size == capacity)
    {
        capacity *= 2;
        T * dest = new T[capacity];
        for (size_t i = 0; i < size; ++i)
        {
            dest[i] = data[i];
        }
        delete[] data;
        data = dest;
    }
    data[size] = value;
    ++size;
}
