#include <iomanip>
#include <iostream>
#include <array>
#include <unordered_map>

class ReadingManager
{
public:
    ReadingManager() : total_users(0)
    {
        pages_rating.fill(0.0);
        users_on_page.fill(0);
    }

    void
    Read(int user_id, int page_count)
    {
        if (user_to_page.count(user_id))
        {
            --users_on_page[user_to_page[user_id]];
        }
        else
        {
            ++total_users;
        }
        user_to_page[user_id] = page_count;
        ++users_on_page[user_to_page[user_id]];

        if (total_users == 1)
        {
            pages_rating[page_count] = 1.0;
        }
        else
        {
            int curr_user_read_more_then = 0;
            for (size_t i = 0; i < users_on_page.size(); ++i)
            {
                if (users_on_page[i] != 0)
                {
                    pages_rating[i] = static_cast<double>(curr_user_read_more_then) / (total_users - 1);
                    curr_user_read_more_then += users_on_page[i];
                }
            }
        }
    }

    double
    Cheer(int user_id) const
    {
        if (!user_to_page.count(user_id))
        {
            return 0.0;
        }
        return pages_rating[user_to_page.at(user_id)];
    }

private:
    std::unordered_map<int, int> user_to_page;
    std::array<double, 1001> pages_rating;
    std::array<int, 1001> users_on_page;
    int total_users;
};

int
main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    std::cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id)
    {
        std::string query_type;
        std::cin >> query_type;
        int user_id;
        std::cin >> user_id;

        if (query_type == "READ")
        {
            int page_count;
            std::cin >> page_count;
            manager.Read(user_id, page_count);
        }
        else if (query_type == "CHEER")
        {
            std::cout << std::setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}