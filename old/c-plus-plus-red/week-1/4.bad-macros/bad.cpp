#include "test_runner.h"

#include <ostream>
using namespace std;

template <typename T, typename S>
void print(std::ostream & os, T x, S y)
{
    os << x << endl << y << endl;
}

#define PRINT_VALUES(out, x, y) print(out, x, y)

int mult(int x, int y)
{
    return x * y;
}

void Test1()
{
    ostringstream output;
    PRINT_VALUES(output, 5, 10 - 10);
    ASSERT_EQUAL(output.str(), "5\n0\n");
}

void Test2()
{
    ostringstream output;
    PRINT_VALUES(output, mult(1, 0) + 10, mult(1, 0) * 10);
    ASSERT_EQUAL(output.str(), "10\n0\n");
}

void Test3()
{
    ostringstream output;
    for (int i = 0; i < 3; ++i)
        PRINT_VALUES(output, '1', i);

    ASSERT_EQUAL(output.str(), "1\n0\n1\n1\n1\n2\n");
}

void Test4()
{
    ostringstream output;
    for (int i = 0; i < 3; ++i)
        PRINT_VALUES(output, '1', i + 1);

    ASSERT_EQUAL(output.str(), "1\n1\n1\n2\n1\n3\n");
}

void Test5()
{
    ostringstream output;
    for (int i = 0; i < 3; ++i)
        PRINT_VALUES(output, i - 1, i + 1);

    ASSERT_EQUAL(output.str(), "-1\n1\n0\n2\n1\n3\n");
}

int main()
{
    TestRunner tr;
    tr.RunTest(
        []
        {
            ostringstream output;
            PRINT_VALUES(output, 5, "red belt");
            ASSERT_EQUAL(output.str(), "5\nred belt\n");
        },
        "PRINT_VALUES usage example");

    RUN_TEST(tr, Test1);
    RUN_TEST(tr, Test2);
    RUN_TEST(tr, Test3);
    RUN_TEST(tr, Test4);
    RUN_TEST(tr, Test5);

    return 0;
}