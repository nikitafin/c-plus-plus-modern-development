#include <map>
#include <string>
#include <vector>

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
        std::string first_name = GetFromHistory(year, first_name_history);
        std::string last_name = GetFromHistory(year, last_name_history);

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

    std::string GetFullNameWithHistory(int year)
    {
        std::string first_name = GetFullNameFromHistory(year, first_name_history);
        std::string last_name = GetFullNameFromHistory(year, last_name_history);

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
    std::string BuildFullName(int year, const std::map<int, std::string> & history)
    {
        std::string result;
        for (const auto & [y, hist] : history)
        {
            if (y <= year)
            {
                result = hist;
            }
        }
        return result;
    }

    std::string BuildFullNameHistory(int year, const std::map<int, std::string> & history)
    {
        std::vector<std::string> hist;
        for (const auto & [y, value] : history)
        {
            if (y <= year)
            {
                hist.push_back(value);
            }
        }
        std::string result;
        if (hist.empty())
        {
            return result;
        }
        else if (hist.size() == 1)
        {
            result = hist.back();
            return result;
        }
        else
        {
            result = hist.back();
            std::string prev = hist.back();
            std::vector<std::string> temp;

            for (auto it = hist.rbegin(); it != hist.rend(); ++it)
            {
                if (*it != prev)
                {
                    temp.push_back(*it);
                }
                prev = *it;
            }

            if (!temp.empty())
            {
                result += " (";
                bool is_first = true;
                for (const auto & h : temp)
                {
                    if (!is_first)
                    {
                        result += ", ";
                    }
                    is_first = false;
                    result += h;
                }
                result += ")";
            }

            return result;
        }
    }

    std::map<int, std::string> first_name_history;
    std::map<int, std::string> last_name_history;
};