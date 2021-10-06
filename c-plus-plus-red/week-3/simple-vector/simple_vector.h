#pragma once

#include <cstdlib>
#include <algorithm>

// Реализуйте шаблон SimpleVector
template<typename T>
class SimpleVector {
public:
    SimpleVector();
    explicit SimpleVector(size_t size);
    ~SimpleVector();

    T& operator[](size_t index);

    T* begin();
    T* end();

    size_t Size() const;
    size_t Capacity() const;
    void PushBack(const T& value);

private:
    T* data;
    size_t size;
    size_t capacity;
};
template<typename T>
SimpleVector<T>::SimpleVector()
        : data(nullptr), size(0U), capacity(0U)
{

}
template<typename T>
SimpleVector<T>::SimpleVector(size_t size)
        : data(new T[size]), size(size), capacity(size)
{

}
template<typename T>
SimpleVector<T>::~SimpleVector()
{
    delete[] data;
}
template<typename T>
T& SimpleVector<T>::operator[](size_t index)
{
    return data[index];
}
template<typename T>
T* SimpleVector<T>::begin()
{
    return data;
}
template<typename T>
T* SimpleVector<T>::end()
{
    return data+size;
}
template<typename T>
size_t SimpleVector<T>::Size() const
{
    return size;
}
template<typename T>
size_t SimpleVector<T>::Capacity() const
{
    return capacity;
}
template<typename T>
void SimpleVector<T>::PushBack(const T& value)
{
    if (size==capacity) {
        capacity = (capacity==0) ? 1 : capacity*2;
        T* new_data = new T[capacity];
        if (data!=nullptr) {
            std::copy(data, data+size, new_data);
        }
        delete[] data;
        data = new_data;
    }

    data[size] = value;
    size++;
}
