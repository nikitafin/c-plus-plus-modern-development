#include <gtest/gtest.h>
import secondary_index;

namespace modern_cxx::test {

using namespace std;
using namespace modern_cxx::brown;

TEST(SecondaryIndex, TestRangeBoundaries) {
  const int good_karma = 1000;
  const int bad_karma  = -10;

  Database db;
  db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
  db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

  int count = 0;
  db.RangeByKarma(bad_karma, good_karma, [&count](const Record &) {
    ++count;
    return true;
  });

  ASSERT_EQ(2, count);
}

TEST(SecondaryIndex, TestSameUser) {
  Database db;
  db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
  db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

  int count = 0;
  db.AllByUser("master", [&count](const Record &) {
    ++count;
    return true;
  });

  ASSERT_EQ(2, count);
}

TEST(SecondaryIndex, TestReplacement) {
  const string final_body = "Feeling sad";

  Database db;
  db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
  db.Erase("id");
  db.Put({"id", final_body, "not-master", 1536107260, -10});

  auto record = db.GetById("id");
  ASSERT_NE(record, nullptr);
  ASSERT_EQ(final_body, record->title);
}

} // namespace modern_cxx::test