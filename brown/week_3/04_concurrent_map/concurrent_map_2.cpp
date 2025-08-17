#include <cassert>
#include <cstddef>
#include <mutex>
#include <stdexcept>
#include <unordered_map>
#include <vector>

template <typename K, typename V, typename Hash = std::hash<K>>
class ConcurrentMap {
 public:
  using MapType = std::unordered_map<K, V, Hash>;

  struct WriteAccess {
    V& ref_to_value;
    std::unique_lock<std::mutex> lock;
  };

  struct ReadAccess {
    const V& ref_to_value;
    std::unique_lock<std::mutex> lock;
  };

  explicit ConcurrentMap(size_t bucket_count)
      : bucket_count_(bucket_count),
        submaps_(bucket_count),
        mutexes_(bucket_count) {}

  WriteAccess operator[](const K& key) {
    const size_t index = CalculateSubmapIndex(key);
    std::mutex& mutex = mutexes_[index];
    MapType& map = submaps_[index];
    std::unique_lock lock{mutex};
    return {map[key], std::move(lock)};
  }
  ReadAccess At(const K& key) const {
    const size_t index = CalculateSubmapIndex(key);
    std::mutex& mutex = mutexes_[index];
    const MapType& map = submaps_[index];
    std::unique_lock lock{mutex};
    return {map.at(key), std::move(lock)};
  }

  bool Has(const K& key) const {
    const size_t index = CalculateSubmapIndex(key);
    std::lock_guard lock(mutexes_.at(index));
    const MapType& map = submaps_.at(index);
    return map.count(key) > 0;
  }

  MapType BuildOrdinaryMap() const {
    MapType result;
    for (size_t i = 0; i < bucket_count_; ++i) {
      const std::lock_guard lock(mutexes_.at(i));
      const MapType& map = submaps_.at(i);
      result.insert(map.cbegin(), map.cend());
    }
    return result;
  }

 private:
  size_t CalculateSubmapIndex(const K& key) const {
    return hasher_(key) % bucket_count_;
  }

 private:  // NOLINT
  Hash hasher_;
  size_t bucket_count_ = 0;
  std::vector<MapType> submaps_;
  mutable std::vector<std::mutex> mutexes_;
};

#if defined(WITH_TESTS)
#  include <algorithm>
#  include <future>
#  include <numeric>
#  include <random>

#  define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#  include <doctest/doctest.h>

void RunConcurrentUpdates(ConcurrentMap<int, int>& cm, size_t thread_count,
                          int key_count) {
  auto kernel = [&cm, key_count](int seed) {
    std::vector<int> updates(static_cast<size_t>(key_count));
    std::iota(begin(updates), end(updates), -key_count / 2);
    std::shuffle(begin(updates), end(updates),
                 std::default_random_engine(static_cast<unsigned int>(seed)));

    for (int i = 0; i < 2; ++i) {
      for (auto key : updates) {
        cm[key].ref_to_value++;
      }
    }
  };

  std::vector<std::future<void>> futures;
  futures.reserve(thread_count);
  for (size_t i = 0; i < thread_count; ++i) {
    futures.push_back(std::async(kernel, i));
  }
}

struct Point {
  int x, y;
};

struct PointHash {
  size_t operator()(Point p) const {
    std::hash<int> h;
    return h(p.x) * 3571 + h(p.y);
  }
};

bool operator==(Point lhs, Point rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

TEST_SUITE("Unittest: Concurrent Map 2") {
  TEST_CASE("Concurrent Update") {
    const size_t thread_count = 3;
    const size_t key_count = 50000;

    ConcurrentMap<int, int> cm(thread_count);
    RunConcurrentUpdates(cm, thread_count, key_count);

    const auto result = std::as_const(cm).BuildOrdinaryMap();
    CHECK_EQ(result.size(), key_count);
    for (const auto& [k, v] : result) {
      CHECK_EQ(v, 6);
    }
  }
  TEST_CASE("Read and Write") {
    ConcurrentMap<size_t, std::string> cm(5);

    auto updater = [&cm] {
      for (size_t i = 0; i < 50000; ++i) {
        cm[i].ref_to_value += 'a';
      }
    };
    auto reader = [&cm] {
      std::vector<std::string> result(50000);
      for (size_t i = 0; i < result.size(); ++i) {
        result[i] = cm[i].ref_to_value;
      }
      return result;
    };

    auto u1 = std::async(updater);
    auto r1 = std::async(reader);
    auto u2 = std::async(updater);
    auto r2 = std::async(reader);

    u1.get();
    u2.get();

    for (auto f : {&r1, &r2}) {
      auto result = f->get();
      CHECK(std::all_of(result.begin(), result.end(), [](const std::string& s) {
        return s.empty() || s == "a" || s == "aa";
      }));
    }
  }
  TEST_CASE("Const Access") {
    const std::unordered_map<int, std::string> expected = {
        {1, "one"},
        {2, "two"},
        {3, "three"},
        {31, "thirty one"},
        {127, "one hundred and twenty seven"},
        {1598, "fifteen hundred and ninety eight"}};

    const ConcurrentMap<int, std::string> cm = [&expected] {
      ConcurrentMap<int, std::string> result(3);
      for (const auto& [k, v] : expected) {
        result[k].ref_to_value = v;
      }
      return result;
    }();

    std::vector<std::future<std::string>> futures;
    futures.reserve(10);
    for (int i = 0; i < 10; ++i) {
      futures.push_back(std::async([&cm, i] {
        try {
          return cm.At(i).ref_to_value;
        } catch (std::exception&) {
          return std::string();
        }
      }));
    }
    futures.clear();

    CHECK_EQ(cm.BuildOrdinaryMap(), expected);
  }

  TEST_CASE("String Keys") {
    const std::unordered_map<std::string, std::string> expected = {
        {"one", "ONE"},
        {"two", "TWO"},
        {"three", "THREE"},
        {"thirty one", "THIRTY ONE"},
    };

    const ConcurrentMap<std::string, std::string> cm = [&expected] {
      ConcurrentMap<std::string, std::string> result(2);
      for (const auto& [k, v] : expected) {
        result[k].ref_to_value = v;
      }
      return result;
    }();

    CHECK_EQ(cm.BuildOrdinaryMap(), expected);
  }
  TEST_CASE("User Type") {
    ConcurrentMap<Point, int, PointHash> point_weight(5);

    std::vector<std::future<void>> futures;
    futures.reserve(1000);
    for (int i = 0; i < 1000; ++i) {
      futures.push_back(std::async(
          [&point_weight, i] { point_weight[Point{i, i}].ref_to_value = i; }));
    }

    futures.clear();

    for (int i = 0; i < 1000; ++i) {
      CHECK_EQ(point_weight.At(Point{i, i}).ref_to_value, i);
    }

    const auto weights = point_weight.BuildOrdinaryMap();
    for (int i = 0; i < 1000; ++i) {
      CHECK_EQ(weights.at(Point{i, i}), i);
    }
  }
  TEST_CASE("Has") {
    ConcurrentMap<int, int> cm(2);
    cm[1].ref_to_value = 100;
    cm[2].ref_to_value = 200;

    const auto& const_map = std::as_const(cm);
    CHECK(const_map.Has(1));
    CHECK(const_map.Has(2));
    CHECK(!const_map.Has(3));
  }
}

#else

#  if 0
void TestSpeedup() {
  {
    ConcurrentMap<int, int> single_lock(1);

    LOG_DURATION("Single lock");
    RunConcurrentUpdates(single_lock, 4, 50000);
  }
  {
    ConcurrentMap<int, int> many_locks(100);

    LOG_DURATION("100 locks");
    RunConcurrentUpdates(many_locks, 4, 50000);
  }
}
#  endif

#endif