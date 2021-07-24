#include <algorithm>
#include <string>
#include <vector>
#include <set>

class Learner
{
private:
    std::set<std::string> dict;

public:
    int
    Learn(const std::vector<std::string> &words)
    {
        int newWords = 0;
        for (const auto &word : words)
        {
            if (!dict.count(word))
            {
                dict.insert(word);
                ++newWords;
            }
        }
        return newWords;
    }

    std::vector<std::string>
    KnownWords()
    {
        return {dict.begin(), dict.end()};
    }
};
