#include <exception>
#include <iostream>
#include <string>

class TimeServer
{
public:
    std::string GetCurrentTime()
    {
        try
        {
            auto res = AskTimeServer();
            last_fetched_time = res;
            return res;
        }
        catch (const std::system_error & e)
        {
            return last_fetched_time;
        }
    }

private:
    std::string last_fetched_time = "00:00:00";
};
