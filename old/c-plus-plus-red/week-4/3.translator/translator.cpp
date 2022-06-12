#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "test_runner.h"

using namespace std;

class Translator
{
public:
    Translator() : strings()
    {
    }
    void Add(string_view source, string_view target)
    {
        auto sp = strings.insert(source.data());
        auto tp = strings.insert(target.data());
        source_to_target[*sp.first] = *tp.first;
        target_to_source[*tp.first] = *sp.first;
    }

    string_view TranslateForward(string_view source) const
    {
        if (source_to_target.count(source))
        {
            return source_to_target.find(source)->second;
        }
        return "";
    }

    string_view TranslateBackward(string_view target) const
    {
        if (target_to_source.count(target))
        {
            return target_to_source.find(target)->second;
        }
        return "";
    }

private:
    std::unordered_set<std::string> strings;
    std::unordered_map<std::string_view, std::string_view> source_to_target;
    std::unordered_map<std::string_view, std::string_view> target_to_source;
};

void TestSimple()
{
    Translator translator;
    translator.Add(string("okno"), string("window"));
    translator.Add(string("stol"), string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    return 0;
}
