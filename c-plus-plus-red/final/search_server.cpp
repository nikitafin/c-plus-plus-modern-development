#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>

std::vector<std::string_view>
SplitIntoWords(std::string_viewline) {
  std::vector<std::string_view> result;
    size_t curr = line.find_first_not_of(' ', 0);
  while (true)
    {
        auto space = line.find(' ', curr);
        result.emplace_back(line.substr(curr, space - curr));

        if (space == line.npos)
        {
            break;
        }
        else
        {
            curr = line.find_first_not_of(' ', space);
        }

        if (curr == line.npos) break;
    }
    return result;
}

SearchServer::SearchServer(istream &document_input) {
  UpdateDocumentBase(document_input);
}

void
SearchServer::UpdateDocumentBase(istream &document_input) {
  InvertedIndex new_index;

  for (string current_document; getline(document_input, current_document);) {
    new_index.Add(move(current_document));
  }

  index = move(new_index);
}

void
SearchServer::AddQueriesStream(istream &query_input,
                               ostream &search_results_output) {
  for (string current_query; getline(query_input, current_query);) {
    const auto words = SplitIntoWords(current_query);

    map<size_t, size_t> docid_count;
    for (const auto &word : words) {
      for (const size_t docid : index.Lookup(word)) {
        docid_count[docid]++;
      }
    }

    vector<pair<size_t, size_t>> search_results(docid_count.begin(),
                                                docid_count.end());
    sort(begin(search_results), end(search_results),
         [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
           int64_t lhs_docid  = lhs.first;
           auto lhs_hit_count = lhs.second;
           int64_t rhs_docid  = rhs.first;
           auto rhs_hit_count = rhs.second;
           return make_pair(lhs_hit_count, -lhs_docid) >
                  make_pair(rhs_hit_count, -rhs_docid);
         });

    search_results_output << current_query << ':';
    for (auto [docid, hitcount] : Head(search_results, 5)) {
      search_results_output << " {"
                            << "docid: " << docid << ", "
                            << "hitcount: " << hitcount << '}';
    }
    search_results_output << endl;
  }
}

void
InvertedIndex::Add(const string &document) {
  docs.push_back(document);

  const size_t docid = docs.size() - 1;
  for (const auto &word : SplitIntoWords(document)) {
    index[word].push_back(docid);
  }
}

list<size_t>
InvertedIndex::Lookup(const string &word) const {
  if (auto it = index.find(word); it != index.end()) {
    return it->second;
  } else {
    return {};
  }
}
