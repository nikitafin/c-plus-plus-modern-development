#include <iostream>
#include <map>
#include <string>
#include <queue>

#include "test_runner.h"

const int64_t kSecInDay = 86400;

struct Reservation {
  int64_t time;
  std::string hotel_name;
  int64_t client_id;
  int64_t rooms_count;
};

class HotelReservationSystem {
private:
  std::queue<Reservation> reservations;
  std::map<std::string, int64_t> hotel_to_room_count;
  std::map<std::string, std::map<int64_t, int64_t>> hotel_to_client_count;

  int64_t current_time = 0;

  void
  updateReservationQuery();
public:
  HotelReservationSystem();

  void
  Book(int64_t time, const std::string &hotel_name, int64_t client_id, int64_t room_count);

  int64_t
  Clients(const std::string &hotel_name) const;

  int64_t
  Rooms(const std::string &hotel_name) const;

};

HotelReservationSystem::HotelReservationSystem() = default;

void
HotelReservationSystem::Book(int64_t time,
                             const std::string &hotel_name,
                             int64_t client_id,
                             int64_t room_count) {
  current_time = time;
  reservations.push({time, hotel_name, client_id, room_count});
  hotel_to_room_count[hotel_name] += room_count;
  ++hotel_to_client_count[hotel_name][client_id];

  updateReservationQuery();
}

int64_t
HotelReservationSystem::Clients(const std::string &hotel_name) const {
  if (hotel_to_client_count.count(hotel_name) == 0U) {
    return 0;
  }
  return hotel_to_client_count.at(hotel_name).size();
}

int64_t
HotelReservationSystem::Rooms(const std::string &hotel_name) const {
  if (hotel_to_room_count.count(hotel_name) == 0U) {
    return 0;
  }
  return hotel_to_room_count.at(hotel_name);
}

void
HotelReservationSystem::updateReservationQuery() {
  while (!reservations.empty() && reservations.front().time <= current_time - kSecInDay) {
    auto &res = reservations.front();
    hotel_to_room_count[res.hotel_name] -= res.rooms_count;
    --hotel_to_client_count[res.hotel_name][res.client_id];
    if (hotel_to_client_count[res.hotel_name][res.client_id] == 0) {
      hotel_to_client_count[res.hotel_name].erase(res.client_id);
    }
    reservations.pop();
  }
}

void
Test0() {
  HotelReservationSystem hsr;
  ASSERT_EQUAL(hsr.Clients("Marriott"), 0)
  ASSERT_EQUAL(hsr.Rooms("Marriott"), 0)
  hsr.Book(10, "FourSeasons", 1, 2);
  hsr.Book(10, "Marriott", 1, 1);
  hsr.Book(86409, "FourSeasons", 2, 1);
  ASSERT_EQUAL(hsr.Clients("FourSeasons"), 2)
  ASSERT_EQUAL(hsr.Rooms("FourSeasons"), 3)
  ASSERT_EQUAL(hsr.Clients("Marriott"), 1)
  hsr.Book(86410, "Marriott", 2, 10);
  ASSERT_EQUAL(hsr.Rooms("FourSeasons"), 1)
  ASSERT_EQUAL(hsr.Rooms("Marriott"), 10)
}

int
main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  HotelReservationSystem hsr;
  int64_t query_count = 0;
  std::cin >> query_count;
  for (int query_id = 0; query_id < query_count; ++query_id) {
    std::string query_type;
    std::cin >> query_type;

    std::string hotel_name;
    if (query_type == "BOOK") {
      int64_t time, client_id, room_count;
      std::cin >> time >> hotel_name >> client_id >> room_count;
      hsr.Book(time, hotel_name, client_id, room_count);
    } else if (query_type == "CLIENTS") {
      std::cin >> hotel_name;
      std::cout << hsr.Clients(hotel_name) << "\n";
    } else if (query_type == "ROOMS") {
      std::cin >> hotel_name;
      std::cout << hsr.Rooms(hotel_name) << "\n";
    } else {
      std::cerr << "INVALID QUERY";
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}
