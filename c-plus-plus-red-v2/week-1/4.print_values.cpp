#include "test_runner.h"

#include <ostream>

#define PRINT_VALUES(out, x, y) do{out << (x) << std::endl; out << (y) << std::endl;} while(0)

int
main()
{
    TestRunner tr;
    tr.RunTest([]
               {
                   std::ostringstream output;
                   PRINT_VALUES(output, 5, "red belt");
                   ASSERT_EQUAL(output.str(), "5\nred belt\n");
               }, "PRINT_VALUES usage example");

    return 0;
}
