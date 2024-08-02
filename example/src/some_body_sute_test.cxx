#include <boost/ut.hpp>

namespace ut = boost::ut;
using namespace ut::literals;

ut::suite<"extra suit"> errors = [] {
  using namespace ut;

  "throws"_test = [] {
    expect(throws([] { throw 0; }));
  };

  "doesn't throw"_test = [] {
    expect(nothrow([] {}));
  };
};
