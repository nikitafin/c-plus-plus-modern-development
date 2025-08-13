#include <functional>

template <typename T>
class LazyValue {
 public:
  explicit LazyValue(std::function<T()> init)
      : init_callback_(std::move(init)) {}

  bool HasValue() const {
    return has_value_;
  }

  const T& Get() const {
    static T value = init_callback_();
    has_value_ = true;
    return value;
  }

 private:
  // mutable std::optional<T> value_;
  mutable bool has_value_ = false;
  std::function<T()> init_callback_;
};

#if defined(WITH_TESTS)
#  include <string>

#  define DOCTEST_CONFIG_NO_MULTITHREADING
#  define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#  include <doctest/doctest.h>

TEST_SUITE("Unittest: LazyValue") {
  TEST_CASE("Using Example") {
    const std::string big_string = "Giant amounts of memory";

    LazyValue<std::string> lazy_string(
        [&big_string] { return big_string; });  // NOLINT

    CHECK(!lazy_string.HasValue());
    CHECK_EQ(lazy_string.Get(), big_string);
    CHECK_EQ(lazy_string.Get(), big_string);
  }
  TEST_CASE("Check InitCallback does not called") {
    bool called = false;
    {
      LazyValue<int> lazy_int([&called] {
        called = true;
        return 0;
      });
    }
    CHECK(!called);
  }
}

#endif
