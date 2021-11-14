#include <iostream>
#include <map>
#include <vector>

using dict = std::map<std::string, std::vector<std::string>>;

void NewBus(dict &bus_stops,
            dict &stop_buses,
            const std::string &bus,
            const std::vector<std::string> &stops) {

  bus_stops[bus].insert(bus_stops[bus].end(), stops.begin(), stops.end());
  for (const auto &stop: stops) {
    stop_buses[stop].push_back(bus);
  }
}

void BusesForStop(const dict &stop_buses, const std::string &stop) {
  if (stop_buses.count(stop) == 0) {
    std::cout << "No stop" << std::endl;
  } else {
    bool first = true;
    for (const auto &bus: stop_buses.at(stop)) {
      if (!first) {
        std::cout << " ";
      }
      first = false;
      std::cout << bus;
    }
    std::cout << std::endl;
  }
}

void StopsForBus(const dict &bus_stops, const dict &stop_buses, const std::string &bus) {
  if (bus_stops.count(bus) == 0) {
    std::cout << "No bus" << std::endl;
  } else {
    for (const auto &stop: bus_stops.at(bus)) {
      std::cout << "Stop " << stop << ": ";
      if (stop_buses.at(stop).size() == 1) {
        std::cout << "no interchange" << std::endl;
      } else {
        bool first = true;
        for (const auto &sbus: stop_buses.at(stop)) {
          if (sbus != bus) {
            if (!first) {
              std::cout << " ";
            }
            first = false;
            std::cout << sbus;
          }
        }
        std::cout << std::endl;
      }
    }
  }
}

void AllBuses(const dict &bus_stops) {
  if (bus_stops.empty()) {
    std::cout << "No buses" << std::endl;
  } else {
    for (const auto&[bus, stops]: bus_stops) {
      bool first = true;
      std::cout << "Bus " << bus << ": ";
      for (const auto &stop: stops) {
        if (!first) {
          std::cout << " ";
        }
        first = false;
        std::cout << stop;
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
}

int main() {
  dict bus_stops;
  dict stop_buses;
  int cmd_count = 0;
  std::cin >> cmd_count;
  for (int i = 0; i < cmd_count; ++i) {
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "NEW_BUS") {
      std::string bus;
      int stops_count;
      std::cin >> bus >> stops_count;
      std::vector<std::string> stops(stops_count);
      for (auto &stop: stops) {
        std::cin >> stop;
      }
      NewBus(bus_stops, stop_buses, bus, stops);
    } else if (cmd == "BUSES_FOR_STOP") {
      std::string stop;
      std::cin >> stop;
      BusesForStop(stop_buses, stop);
    } else if (cmd == "STOPS_FOR_BUS") {
      std::string bus;
      std::cin >> bus;
      StopsForBus(bus_stops, stop_buses, bus);
    } else {
      AllBuses(bus_stops);
    }
  }

  return 0;
}