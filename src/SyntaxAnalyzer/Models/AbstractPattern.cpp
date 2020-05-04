#include "AbstractPattern.hpp"

std::vector<char> AbstractPattern::whitespaces = { '\n', ' ', '\t', 12 };

void AbstractPattern::skipWhitespacesCharacters(const Range& range) const {
  while (range.first != range.second && std::find(whitespaces.begin(), whitespaces.end(), *range.first) != whitespaces.end())
    range.first++;
}

std::string AbstractPattern::prefix(const Range& range) const {
  if (range.second - range.first > begin.size() && std::string(range.first, range.first + begin.size()) == begin)
    return begin;
  return "";
}
