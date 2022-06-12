#include <map>
#include <string>

class Person
{
public:
    void ChangeFirstName(int year, const std::string & first_name)
    {
        first_name_history[year] = first_name;
    }
    void ChangeLastName(int year, const std::string & last_name)
    {
        last_name_history[year] = last_name;
    }
    std::string GetFullName(int year)
    {
        std::string first_name, last_name;
        for (const auto & [y, fn] : first_name_history)
        {
            if (y <= year)
            {
                first_name = fn;
            }
        }
        for (const auto & [y, ln] : last_name_history)
        {
            if (y <= year)
            {
                last_name = ln;
            }
        }
        if (first_name.empty() and last_name.empty())
        {
            return "Incognito";
        }
        else if (!first_name.empty() and last_name.empty())
        {
            return first_name + " with unknown last name";
        }
        else if (first_name.empty() and !last_name.empty())
        {
            return last_name + " with unknown first name";
        }
        else
        {
            return first_name + " " + last_name;
        }
    }

private:
    std::map<int, std::string> first_name_history;
    std::map<int, std::string> last_name_history;
};