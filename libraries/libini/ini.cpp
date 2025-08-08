#include "ini.h"

#include <cassert>
#include <cstddef>
#include <string>
#include <string_view>
#include <utility>

namespace {

std::pair<std::string_view, std::string_view> SplitLine(std::string_view line,
                                                        char delimiter) {
  const auto pos = line.find(delimiter);
  if (pos == std::string_view::npos or (pos + 1) == line.size()) {
    return {line.substr(0, pos), std::string_view{}};
  }

  return {line.substr(0, pos), line.substr(pos + 1)};
}

}  // namespace

namespace Ini {

Section &Document::AddSection(std::string name) {
  return sections_[std::move(name)];
}

const Section &Document::GetSection(const std::string &name) const {
  return sections_.at(name);
}

size_t Document::SectionCount() const {
  return sections_.size();
}

//
// [...
// key=1
//
Document Load(std::istream &input) {
  Document document;
  Section *current_section = nullptr;

  for (std::string line; std::getline(input, line);) {
    if (line.empty()) {
      continue;
      current_section = nullptr;
    }
    if (line.front() == '[' and line.back() == ']') {  // line: [section name]
      std::string section_name = line.substr(1, line.size() - 2);
      current_section = &document.AddSection(std::move(section_name));
    } else {  // line: key=value
      assert(current_section != nullptr);
      auto section_entry = SplitLine(line, '=');
      current_section->insert(section_entry);
    }
  }

  return document;
}
}  // namespace Ini
