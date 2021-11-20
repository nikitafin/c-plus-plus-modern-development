
#include "stats.h"

void Stats::AddMethod(string_view method) {
  if (methodStats.count(method)) {
    methodStats[method]++;
  } else {
    methodStats["UNKNOWN"]++;
  }
}
void Stats::AddUri(string_view uri) {
  if (uriStats.count(uri)) {
    uriStats[uri]++;
  } else {
    uriStats["unknown"]++;
  }
}
const map<string_view, int> &Stats::GetMethodStats() const {
  return methodStats;
}
const map<string_view, int> &Stats::GetUriStats() const {
  return uriStats;
}

HttpRequest ParseRequest(string_view line) {
  HttpRequest request;
  line.remove_prefix(line.find_first_not_of(" \n\r"));

  auto space = line.find(' ');
  request.method = line.substr(0, space);
  line.remove_prefix(space + 1);

  space = line.find(' ');
  request.uri = line.substr(0, space);
  line.remove_prefix(space + 1);

  request.protocol = line;

  return request;
}
