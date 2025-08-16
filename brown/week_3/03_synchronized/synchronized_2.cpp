#include <mutex>
#include <utility>

template <typename T>
struct BlockedRef final {
  BlockedRef(T &value, std::mutex &mutex) : ref_to_value(value), mutex_(mutex) {
    mutex_.lock();
  }
  ~BlockedRef() { mutex_.unlock(); }

  T &ref_to_value;

 private:
  std::mutex &mutex_;
};

template <typename T>
struct ConstBlockedRef final {
  ConstBlockedRef(const T &value, std::mutex &mutex)
      : ref_to_value(value), mutex_(mutex) {
    mutex_.lock();
  }
  ~ConstBlockedRef() { mutex_.unlock(); }

  const T &ref_to_value;

 private:
  std::mutex &mutex_;
};

template <typename T>
class Synchronized {
 public:
  explicit Synchronized(T initial = T()) : value_(std::move(initial)) {}

  BlockedRef<T> GetAccess() { return {value_, mutex_}; }
  ConstBlockedRef<T> GetAccess() const { return {value_, mutex_}; }

 private:
  T value_;
  mutable std::mutex mutex_;
};

#if defined(WITH_TESTS)
#  include <future>
#  include <numeric>
#  include <queue>
#  include <string>
#  include <vector>

#  define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#  include <doctest/doctest.h>

std::vector<int> Consume(Synchronized<std::deque<int>> &common_queue) {
  std::vector<int> got;

  for (;;) {
    std::deque<int> q;

    {
      // Мы специально заключили эти две строчки в операторные скобки, чтобы
      // уменьшить размер критической секции. Поток-потребитель захватывает
      // мьютекс, перемещает всё содержимое общей очереди в свою
      // локальную переменную и отпускает мьютекс. После этого он обрабатывает
      // объекты в очереди за пределами критической секции, позволяя
      // потоку-производителю параллельно помещать в очередь новые объекты.
      //
      // Размер критической секции существенно влияет на быстродействие
      // многопоточных программ.
      auto access = common_queue.GetAccess();
      q = std::move(access.ref_to_value);
    }

    for (int item : q) {
      if (item > 0) {
        got.push_back(item);
      } else {
        return got;
      }
    }
  }
}

void Log(const Synchronized<std::deque<int>> &common_queue, std::ostream &out) {
  for (int i = 0; i < 100; ++i) {  // NOLINT (*-magic-numbers)
    out << "Queue size is " << common_queue.GetAccess().ref_to_value.size()
        << '\n';
  }
}

TEST_SUITE("Unittest: Synchronized") {
  TEST_CASE("Concurrent Update") {
    Synchronized<std::string> common_string;

    const size_t add_count = 50000;
    auto updater = [&common_string] {
      for (size_t i = 0; i < add_count; ++i) {
        auto access = common_string.GetAccess();
        access.ref_to_value += 'a';
      }
    };

    auto f1 = std::async(updater);  // NOLINT (*-identifier-length)
    auto f2 = std::async(updater);  // NOLINT (*-identifier-length)

    f1.get();
    f2.get();

    CHECK_EQ(common_string.GetAccess().ref_to_value.size(), 2 * add_count);
  }
  TEST_CASE("Produces consumer") {
    Synchronized<std::deque<int>> common_queue;
    std::ostringstream log;

    auto consumer = std::async(Consume, std::ref(common_queue));
    auto logger = std::async(Log, std::cref(common_queue), std::ref(log));

    const size_t item_count = 100'000;
    for (int i = 1; i <= static_cast<int>(item_count); ++i) {
      common_queue.GetAccess().ref_to_value.push_back(i);
    }
    common_queue.GetAccess().ref_to_value.push_back(-1);

    std::vector<int> expected(item_count);
    std::iota(std::begin(expected), std::end(expected), 1);
    CHECK_EQ(consumer.get(), expected);

    logger.get();
    const std::string logs = log.str();
    CHECK(!logs.empty());
  }
}

#endif