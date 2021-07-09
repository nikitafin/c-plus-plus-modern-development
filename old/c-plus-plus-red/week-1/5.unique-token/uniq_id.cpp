#include <string>
#include <vector>

using namespace std;

#define f(a, b) a##b
#define g(a) f(id_, a)
#define UNIQ_ID g(__LINE__)

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};

  return 0;
}