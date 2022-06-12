#pragma once

#include <map>
#include <set>
#include <string_view>

#include "http_request.h"

class Stats
{
public:
    void AddMethod(std::string_view method);
    void AddUri(std::string_view uri);
    const std::map<std::string_view, int> & GetMethodStats() const;
    const std::map<std::string_view, int> & GetUriStats() const;

private:
    std::map<std::string_view, int> methodCount{
        {"GET", 0}, {"POST", 0}, {"PUT", 0}, {"DELETE", 0}, {"UNKNOWN", 0}};

    std::map<std::string_view, int> uriCount{
        {"/", 0},
        {"/order", 0},
        {"/product", 0},
        {"/basket", 0},
        {"/help", 0},
        {"unknown", 0}};
    //  std::set<std::string> methods{"GET", "POST", "PUT", "DELETE", "UNKNOWN"};
    //  std::set<std::string> uris{"/", "/order", "/product", "/basket", "/help"};
};

HttpRequest ParseRequest(std::string_view line);
