#include <stdint.h>

#include <algorithm>
#include <future>
#include <numeric>
#include <thread>
#include <vector>

#include "profile.h"
#include "test_runner.h"
using namespace std;

template <typename Iterator>
class Page
{
private:
    Iterator first, last;

public:
    Page(Iterator first, Iterator last) : first(first), last(last)
    {
    }
    size_t size() const
    {
        return std::distance(first, last);
    }
    auto begin()
    {
        return first;
    }
    auto end()
    {
        return last;
    }
    auto begin() const
    {
        return first;
    }
    auto end() const
    {
        return last;
    }
};

template <typename Iterator>
class Paginator
{
public:
    Paginator(Iterator begin, Iterator end, size_t page_size)
    {
        size_t container_size = std::distance(begin, end);
        do
        {
            auto page_end = std::next(begin, std::min(page_size, container_size));
            if (begin != page_end)
            {
                elements.push_back({begin, page_end});
            }
            begin = page_end;
            container_size -= std::min(page_size, container_size);
        } while (container_size > 0);
    }
    size_t size() const
    {
        return elements.size();
    }

    auto begin()
    {
        return elements.begin();
    }
    auto end()
    {
        return elements.end();
    }

    auto begin() const
    {
        return elements.cbegin();
    }
    auto end() const
    {
        return elements.cend();
    }

private:
    std::vector<Page<Iterator>> elements;
};

template <typename C>
auto Paginate(C & c, size_t page_size)
{
    return Paginator(c.begin(), c.end(), page_size);
}

template <typename Matrix>
int64_t CalculateMatrixSingleThread(const Matrix & matrix)
{
    int64_t result = 0;
    for (const auto & row : matrix)
    {
        result += std::accumulate(row.begin(), row.end(), 0);
    }

    return result;
}

int64_t CalculateMatrixSum(const vector<vector<int>> & matrix)
{
    size_t page_size = 2000;
    vector<future<int64_t>> futures;
    for (auto page : Paginate(matrix, page_size))
    {
        futures.push_back(async([=]() { return CalculateMatrixSingleThread(page); }));
    }
    int64_t result = 0;
    for (auto & f : futures)
    {
        result += f.get();
    }

    return result;
}

void TestCalculateMatrixSum()
{
    const vector<vector<int>> matrix
        = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

template <typename ContainerOfVectors>
void GenerateSingleThread(
    ContainerOfVectors & result, size_t first_row, size_t column_size)
{
    for (auto & row : result)
    {
        row.reserve(column_size);
        for (size_t column = 0; column < column_size; ++column)
        {
            row.push_back(first_row ^ column);
        }
        ++first_row;
    }
}

vector<vector<int>> GenerateMultiThread(size_t size, size_t page_size)
{
    vector<vector<int>> result(size);
    vector<future<void>> futures;
    size_t first_row = 0;
    for (auto page : Paginate(result, page_size))
    {
        futures.push_back(async([page, first_row, size]
                                { GenerateSingleThread(page, first_row, size); }));
        first_row += page_size;
    }
    return result;
}

void Test()
{
    std::vector<std::vector<int>> matrix;
    {
        LOG_DURATION("Matrix Generate");
        matrix = GenerateMultiThread(9000, 3000);
    }
    int64_t res;
    {
        LOG_DURATION("Matrix Sum");
        res = CalculateMatrixSum(matrix);
    }
    std::cout << res << std::endl;
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);
    RUN_TEST(tr, Test);
}
