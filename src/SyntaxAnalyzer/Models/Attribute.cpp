#include "Attribute.hpp"

bool Attribute::consume(const Range& range, const EmitFunction& func) const  {
  auto tmp = range.first;
  Range tmpRange(tmp, range.second);

  if (begin == AbstractPattern::prefix(tmpRange)) {
    tmp += begin.size();
    // Skip whitespaces
    AbstractPattern::skipWhitespacesCharacters(tmpRange);
    // Check for =
    if (std::string(1, *tmp) != separator || separator == "")
      return false;
    // Skip whitespaces
    AbstractPattern::skipWhitespacesCharacters(tmpRange);
    tmp++;
    if (*tmp == '\'' || *tmp == '\"') {
      auto quoteIndex = std::find(tmp + 1, range.second, *tmp);
      tmp++;
      func(std::pair<int, int>(tmp - range.first, quoteIndex - range.first));
      range.first = quoteIndex + 1;
      return true;
    }
  }

  return false;
}
