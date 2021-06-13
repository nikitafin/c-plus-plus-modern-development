#include <string>
#include <vector>

#define GLUE_HELPER(x, y) x##y
#define GLUE(x, y) GLUE_HELPER(x, y)
#define UNIQ_ID GLUE(id, __LINE__)

int
main()
{
    int UNIQ_ID = 0;
    std::string UNIQ_ID = "hello";
    std::vector<std::string> UNIQ_ID = {"hello", "world"};
    std::vector<int> UNIQ_ID = {1, 2, 3, 4};
}