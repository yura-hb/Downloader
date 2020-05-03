#include "Attribute.hpp"

bool Attribute::consume(const Range& range, const EmitFunction& func) const  {
  auto tmp = range.first;
  Range tmpRange = std::pair<std::string::iterator&, const std::string::iterator&>(tmp, range.second);

  if (this -> begin == prefix(tmpRange)) {
    // Skip whitespaces
    AbstractPattern::skipWhitespacesCharacters(tmpRange);
    tmp++;
    // Check for =
    if (std::to_string(*tmp) != separator)
      return false;
    // Skip whitespaces
    AbstractPattern::skipWhitespacesCharacters(tmpRange);
    tmp++;

    if (*tmp == '\'' || *tmp == '\"') {
      auto quoteIndex = std::find(tmp, range.second, *tmp);
      func(std::pair<int, int>(tmp - range.first, quoteIndex - range.first));
      range.first = quoteIndex + 1;
      return true;
    }
  }

  return false;
}
