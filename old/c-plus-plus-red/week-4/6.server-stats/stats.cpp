#include "stats.h"

void Stats::AddMethod(std::string_view method)
{
    std::string data(method);
    if (auto it = methodCount.find(data); it != methodCount.end())
    {
        ++methodCount[it->first];
    }
    else
    {
        ++methodCount["UNKNOWN"];
    }
}

void Stats::AddUri(std::string_view uri)
{
    std::string data(uri);
    if (auto it = uriCount.find(data); it != uriCount.end())
    {
        ++uriCount[it->first];
    }
    else
    {
        ++uriCount["unknown"];
    }
}

const std::map<std::string_view, int> & Stats::GetMethodStats() const
{
    return methodCount;
}

const std::map<std::string_view, int> & Stats::GetUriStats() const
{
    return uriCount;
}

HttpRequest ParseRequest(std::string_view line)
{
    // ltrim
    line.remove_prefix(line.find_first_not_of(" \t\r\f\v\n"));
    size_t space = line.find(' ');
    std::string_view method = line.substr(0, space);
    line.remove_prefix(space + 1);

    space = line.find(' ');
    std::string_view uri = line.substr(0, space);
    line.remove_prefix(space + 1);

    space = line.find(' ');
    std::string_view protocol = line.substr(0, space);

    return {method, uri, protocol};
}
