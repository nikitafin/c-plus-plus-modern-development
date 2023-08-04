#pragma once
#include <mutex>

template <typename T>
class Synchronized
{
public:
    explicit Synchronized(T initial = T()) : value{std::move(initial)}
    {
    }

    struct Access
    {
        Access(std::mutex & m, T & val) : lc{m}, ref_to_value{val}
        {
        }

        std::lock_guard<std::mutex> lc;
        T & ref_to_value;
    };

    Access GetAccess()
    {
        return Access(m, value);
    }

private:
    std::mutex m;
    T value;
};