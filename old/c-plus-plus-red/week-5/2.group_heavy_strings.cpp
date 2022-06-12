#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "test_runner.h"

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = std::vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String>
using Char = typename String::value_type;

template <typename String>
std::vector<Group<String>> GroupHeavyStrings(std::vector<String> strings)
{
    std::map<std::set<Char<String>>, Group<String>> groups;
    for (auto && string : strings)
    {
        std::set<Char<String>> temp;
        for (Char<String> ch : string)
        {
            if (!temp.count(ch))
            {
                temp.insert(std::move(ch));
            }
        }
        groups[std::move(temp)].push_back(std::move(string));
    }
    std::vector<Group<String>> result;
    result.reserve(groups.size());
    for (auto && [key, value] : groups)
    {
        result.push_back(std::move(value));
    }
    return result;
}

void TestGroupingABC()
{
    std::vector<std::string> strings = {"caab", "abc", "cccc", "bacc", "c"};
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 2);
    sort(begin(groups), end(groups)); // Порядок групп не имеет значения
    ASSERT_EQUAL(groups[0], std::vector<std::string>({"caab", "abc", "bacc"}));
    ASSERT_EQUAL(groups[1], std::vector<std::string>({"cccc", "c"}));
}

void TestGroupingReal()
{
    std::vector<std::string> strings
        = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 4);
    sort(begin(groups), end(groups)); // Порядок групп не имеет значения
    ASSERT_EQUAL(groups[0], std::vector<std::string>({"laptop", "paloalto"}));
    ASSERT_EQUAL(groups[1], std::vector<std::string>({"law", "wall", "awl"}));
    ASSERT_EQUAL(groups[2], std::vector<std::string>({"port"}));
    ASSERT_EQUAL(groups[3], std::vector<std::string>({"top", "pot"}));
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestGroupingABC);
    RUN_TEST(tr, TestGroupingReal);
    return 0;
}
