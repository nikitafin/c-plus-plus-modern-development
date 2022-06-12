#include <queue>
#include <unordered_map>

#include "test_runner.h"

struct Booking
{
    std::string hotel_name;
    int64_t time;
    int64_t client_id;
    int64_t room_count;
};

class BookingManager
{
private:
    std::queue<Booking> hotels;
    std::unordered_map<std::string, int64_t> hotel_rooms;
    std::unordered_map<std::string, std::unordered_map<int64_t, int64_t>> hotel_clients;

public:
    BookingManager() = default;
    void Book(
        int64_t time,
        const std::string & hotel_name,
        int64_t client_id,
        int64_t room_count);
    int64_t Clients(const std::string & hotel_name);
    int64_t Rooms(const std::string & hotel_name);
};

void BookingManager::Book(
    int64_t time, const std::string & hotel_name, int64_t client_id, int64_t room_count)
{
    // delete old
    for (auto & hotel = hotels.front();
         hotel.time <= time - static_cast<int64_t>(86400) and !hotels.empty();
         hotel = hotels.front())
    {
        hotel_rooms[hotel.hotel_name] -= hotel.room_count;
        if (hotel_rooms[hotel.hotel_name] == 0)
        {
            hotel_rooms.erase(hotel.hotel_name);
        }
        --hotel_clients[hotel.hotel_name][hotel.client_id];
        if (hotel_clients[hotel.hotel_name][hotel.client_id] == 0)
        {
            hotel_clients[hotel.hotel_name].erase(hotel.client_id);
        }
        hotels.pop();
        if (hotels.empty())
        {
            break;
        }
    }

    hotels.push({hotel_name, time, client_id, room_count});
    hotel_rooms[hotel_name] += room_count;
    ++hotel_clients[hotel_name][client_id];
}

int64_t BookingManager::Clients(const std::string & hotel_name)
{
    if (hotel_clients.count(hotel_name))
    {
        return hotel_clients[hotel_name].size();
    }
    return 0;
}

int64_t BookingManager::Rooms(const std::string & hotel_name)
{
    if (hotel_rooms.count(hotel_name))
    {
        return hotel_rooms[hotel_name];
    }
    return 0;
}

void TestBasic()
{
    BookingManager bm;
    ASSERT_EQUAL(bm.Clients("Marriott"), 0);
    ASSERT_EQUAL(bm.Rooms("Marriott"), 0);
    bm.Book(10, "FourSeasons", 1, 2);
    bm.Book(10, "Marriott", 1, 1);
    bm.Book(86409, "FourSeasons", 2, 1);
    ASSERT_EQUAL(bm.Clients("FourSeasons"), 2);
    ASSERT_EQUAL(bm.Rooms("FourSeasons"), 3);
    ASSERT_EQUAL(bm.Clients("Marriott"), 1);
    bm.Book(86410, "Marriott", 2, 10);
    ASSERT_EQUAL(bm.Rooms("FourSeasons"), 1);
    ASSERT_EQUAL(bm.Rooms("Marriott"), 10);
}

void Test1()
{
    BookingManager bm;
    ASSERT_EQUAL(bm.Rooms("a"), 0);
    ASSERT_EQUAL(bm.Clients("a"), 0);
    bm.Book(-100000, "a", 100000, 1000);
    bm.Book(-100000, "a", 100003, 1000);
    bm.Book(-100000, "b", 100002, 1000);
    ASSERT_EQUAL(bm.Rooms("a"), 2000);
    ASSERT_EQUAL(bm.Clients("a"), 2);
    bm.Book(-10000, "a", 100002, 1000);
    ASSERT_EQUAL(bm.Rooms("a"), 1000);
    ASSERT_EQUAL(bm.Clients("a"), 1);
    ASSERT_EQUAL(bm.Rooms("b"), 0);
    ASSERT_EQUAL(bm.Clients("b"), 0);
}

void Test2()
{
    BookingManager manager;
    std::string marriot{"mariott"};
    std::string hilton{"hilton"};
    // Test empty bookings
    ASSERT_EQUAL(manager.Clients(marriot), 0);
    ASSERT_EQUAL(manager.Rooms(marriot), 0);

    manager.Book(0, "mariott", 1, 10);
    manager.Book(0, "mariott", 2, 1);
    manager.Book(0, "mariott", 3, 1);
    manager.Book(0, "mariott", 4, 1);
    manager.Book(0, "hilton", 1, 1);
    manager.Book(1, "hilton", 2, 1);

    // Test correctness
    ASSERT_EQUAL(manager.Clients(marriot), 4);
    ASSERT_EQUAL(manager.Rooms(marriot), 13);
    ASSERT_EQUAL(manager.Clients(hilton), 2);
    ASSERT_EQUAL(manager.Rooms(hilton), 2);

    // Test event past 1 day resets statics
    manager.Book(86400, "mariott", 1, 1);
    ASSERT_EQUAL(manager.Clients(marriot), 1);
    ASSERT_EQUAL(manager.Rooms(marriot), 1);
    ASSERT_EQUAL(manager.Clients(hilton), 1);
    ASSERT_EQUAL(manager.Rooms(hilton), 1);

    // Test no clients and room for the last day
    manager.Book(86401, "mariott", 5, 1);
    ASSERT_EQUAL(manager.Clients(marriot), 2);
    ASSERT_EQUAL(manager.Rooms(marriot), 2);
    ASSERT_EQUAL(manager.Clients(hilton), 0);
    ASSERT_EQUAL(manager.Rooms(hilton), 0);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    BookingManager booking_manager;
    int query_count{0};
    std::cin >> query_count;
    for (int i = 0; i < query_count; ++i)
    {
        std::string command;
        std::cin >> command;
        if (command == "BOOK")
        {
            int64_t time{0}, client_id{0}, room_count{0};
            std::string hotel_name;
            std::cin >> time >> hotel_name >> client_id >> room_count;
            booking_manager.Book(time, hotel_name, client_id, room_count);
        }
        else if (command == "CLIENTS")
        {
            std::string hotel_name;
            std::cin >> hotel_name;
            std::cout << booking_manager.Clients(hotel_name) << "\n";
        }
        else
        {
            std::string hotel_name;
            std::cin >> hotel_name;
            std::cout << booking_manager.Rooms(hotel_name) << "\n";
        }
    }
    return 0;
}
