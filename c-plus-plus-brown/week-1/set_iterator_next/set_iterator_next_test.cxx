#include <gtest/gtest.h>

import modern_cxx;

using namespace std;
using namespace modern_cxx::brown;

namespace modern_cxx::test {

TEST(Next, Test1) {
  NodeBuilder nb;

  Node *root = nb.CreateRoot(50);
  ASSERT_EQ(root->value, 50);

  Node *l = nb.CreateLeftSon(root, 2);
  Node *min = nb.CreateLeftSon(l, 1);
  Node *r = nb.CreateRightSon(l, 4);
  ASSERT_EQ(min->value, 1);
  ASSERT_EQ(r->parent->value, 2);

  nb.CreateLeftSon(r, 3);
  nb.CreateRightSon(r, 5);

  r = nb.CreateRightSon(root, 100);
  l = nb.CreateLeftSon(r, 90);
  nb.CreateRightSon(r, 101);

  nb.CreateLeftSon(l, 89);
  r = nb.CreateRightSon(l, 91);

  ASSERT_EQ(Next(l)->value, 91);
  ASSERT_EQ(Next(root)->value, 89);
  ASSERT_EQ(Next(min)->value, 2);
  ASSERT_EQ(Next(r)->value, 100);

  while (min) {
    cout << min->value << '\n';
    min = Next(min);
  }
}

TEST(Next, TestRootOnly) {
  NodeBuilder nb;
  Node *root = nb.CreateRoot(42);
  ASSERT_TRUE(Next(root) == nullptr);
};

} // namespace modern_cxx::test
