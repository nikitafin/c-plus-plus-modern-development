#pragma once

#include <chrono>
#include <iostream>
#include <string>

class LogDuration
{
public:
    explicit LogDuration(const std::string & msg = "")
        : message(msg + ": "), start(std::chrono::steady_clock::now())
    {
    }

    ~LogDuration()
    {
        auto finish = std::chrono::steady_clock::now();
        auto dur = finish - start;
        std::cerr << message
                  << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count()
                  << " ms" << std::endl;
    }

private:
    std::string message;
    std::chrono::steady_clock::time_point start;
};

struct TotalDuration
{
    string message;
    std::chrono::steady_clock::duration value;
    explicit TotalDuration(const string & msg = "") : message(msg + ": "), value(0)
    {
    }
    ~TotalDuration()
    {
        ostringstream os;
        os << message << duration_cast<std::chrono::milliseconds>(value).count() << " ms"
           << endl;
        cerr << os.str();
    }
};
class AddDuration
{
public:
    explicit AddDuration(std::chrono::steady_clock::duration & dest)
        : add_to(dest), start(std::chrono::steady_clock::now())
    {
    }
    explicit AddDuration(TotalDuration & dest) : AddDuration(dest.value)
    {
    }
    ~AddDuration()
    {
        add_to += std::chrono::steady_clock::now() - start;
    }

private:
    std::chrono::steady_clock::duration & add_to;
    std::chrono::steady_clock::time_point start;
};

#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)

#define LOG_DURATION(message) LogDuration UNIQ_ID(__LINE__){message};

#define ADD_DURATION(value) \
    AddDuration UNIQ_ID(__LINE__) \
    { \
        value \
    }