#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <list>
#include <set>
#include <tuple>
#include <utility>

#include "test_runner.h"

using namespace std;

template <typename T>
class PriorityCollection
{
public:
    using Id = typename std::list<T>::iterator;

private:
    struct Priority
    {
        using c = std::chrono::system_clock;

        Id object_id;

        int priority{0};
        std::chrono::time_point<c> dt{c::now()};


        Priority(Id id) : object_id{id}
        {
        }

        Priority(Id id, int priority, std::chrono::time_point<c> dt)
            : object_id{id}, priority{priority}, dt{std::move(dt)}
        {
        }


        bool operator<(Priority const other) const
        {
            return std::tie(priority, dt) > std::tie(other.priority, other.dt);
        }
    };


    struct MyOp
    {
        bool operator()(Id const lhs, Id const rhs) const
        {
            return *lhs < *rhs;
        };
    };

    std::list<T> m_data;
    std::set<Priority> m_priority;

    using PriorityId = typename std::set<Priority>::iterator;
    std::map<Id, PriorityId, MyOp> m_id;

public:
    Id Add(T object)
    {
        m_data.push_back(std::move(object));

        Id last_added = std::prev(m_data.end());

        std::pair<PriorityId, bool> d = m_priority.insert(Priority{last_added});
        m_id[last_added] = d.first;

        return last_added;
    }

    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin)
    {
        for (auto it = range_begin; it != range_end; ++it)
        {
            *ids_begin = Add(std::move(*it));
            ++ids_begin;
        }
    }

    bool IsValid(Id id) const
    {
        return m_id.find(id) != m_id.cend();
    }

    const T & Get(Id id) const
    {
        return *id;
    }

    void Promote(Id id)
    {
        PriorityId old_priority_id = m_id[id];
        Priority new_priority{
            old_priority_id->object_id,
            old_priority_id->priority + 1,
            old_priority_id->dt};

        auto [p_id, status] = m_priority.insert(new_priority);
        m_id[old_priority_id->object_id] = p_id;

        m_priority.erase(old_priority_id);
    }

    pair<const T &, int> GetMax() const
    {
        return {*m_priority.begin()->object_id, m_priority.begin()->priority};
    }

    pair<T, int> PopMax()
    {
        Id object_it = m_priority.begin()->object_id;
        int object_priority = m_priority.begin()->priority;

        m_priority.erase(m_priority.begin());
        m_id.erase(m_id.find(object_it));

        pair<T, int> result{std::move(*object_it), object_priority};
        m_data.erase(object_it);

        return result;
    }
};

class StringNonCopyable : public string
{
public:
    using string::string; // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable &) = delete;
    StringNonCopyable(StringNonCopyable &&) = default;
    StringNonCopyable & operator=(const StringNonCopyable &) = delete;
    StringNonCopyable & operator=(StringNonCopyable &&) = default;
};

void TestNoCopy()
{
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");


    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i)
    {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    return 0;
}
