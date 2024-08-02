#include <boost/ut.hpp>

namespace ut = boost::ut;
using namespace ut::literals;

namespace {

int function(int x) {
  if (x > 0) return 42;

  return x;
}

}  // namespace

int main() {
  "some_body"_test = [] {
    int const got = function(-1);
    int const want = -1;

    ut::expect(ut::eq(got, want));
  };
}