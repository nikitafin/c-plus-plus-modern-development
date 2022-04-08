#include <algorithm>
#include <iostream>
#include <list>
#include <unordered_set>

struct sportsman
{
  int number;
  int next;
};

auto
operator< (const sportsman &lhs, const sportsman &rhs) -> bool
{
  return lhs.next < rhs.next;
}

class sportsman_queue
{
public:
  auto
  add (const sportsman &s) -> void
  {
    if (sportsman_numbers.count (s.next) == 0)
      {
        sorted_sportsman.push_back (s.number);
      }
    else
      {
        // ?
        std::find (sorted_sportsman.begin (), sorted_sportsman.end (), s.next);
      }

    sportsman_numbers.insert (s.number);
  }

private:
  std::list<int> sorted_sportsman;
  std::unordered_set<int> sportsman_numbers;
};

int
main ()
{
  std::cout << 123;

  return 0;
}
