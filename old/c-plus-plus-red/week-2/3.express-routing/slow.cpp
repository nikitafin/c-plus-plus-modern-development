#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>

#include "test_runner.h"

class RouteManager
{
public:
    void AddRoute(int start, int finish)
    {
        reachable_lists_[start].insert(finish);
        reachable_lists_[finish].insert(start);
    }

    int FindNearestFinish(int start, int finish) const
    {
        int result = abs(start - finish);
        if (reachable_lists_.count(start) < 1)
        {
            return result;
        }
        const auto & reachable_stations = reachable_lists_.at(start);
        if (!reachable_stations.empty())
        {
            auto searchRes = reachable_stations.lower_bound(finish);
            if (searchRes != reachable_stations.end())
            {
                result = std::min(result, std::abs(finish - *searchRes));
            }
            if (searchRes != reachable_stations.begin())
            {
                result = std::min(result, std::abs(finish - *std::prev(searchRes)));
            }
        }
        return result;
    }

private:
    std::map<int, std::set<int>> reachable_lists_;
};

void TestBasics()
{
    RouteManager rm;
    rm.AddRoute(-2, 5);
    rm.AddRoute(10, 4);
    rm.AddRoute(5, 8);
    ASSERT_EQUAL(rm.FindNearestFinish(4, 10), 0);
    ASSERT_EQUAL(rm.FindNearestFinish(4, -2), 6);
    ASSERT_EQUAL(rm.FindNearestFinish(5, 0), 2);
    ASSERT_EQUAL(rm.FindNearestFinish(5, 100), 92);
}

int main()
{
    TestRunner tr;
    tr.RunTest(TestBasics, "Basics");

    RouteManager routes;

    int query_count;
    std::cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id)
    {
        std::string query_type;
        std::cin >> query_type;
        int start, finish;
        std::cin >> start >> finish;
        if (query_type == "ADD")
        {
            routes.AddRoute(start, finish);
        }
        else if (query_type == "GO")
        {
            std::cout << routes.FindNearestFinish(start, finish) << "\n";
        }
    }

    return 0;
}
