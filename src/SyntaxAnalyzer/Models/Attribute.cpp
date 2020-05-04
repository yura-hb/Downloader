#include "Attribute.hpp"

bool Attribute::consume(const Range& range, const EmitFunction& func) const  {
  auto tmp = range.first;
  Range tmpRange(tmp, range.second);

  if (begin == AbstractPattern::prefix(tmpRange)) {
    std::cout << AbstractPattern::begin << std::endl;
    tmp += begin.size();
    // Skip whitespaces
    AbstractPattern::skipWhitespacesCharacters(tmpRange);
    // Check for =
    std::cout << *tmp << (std::string(1, *tmp) == separator) << begin << "+" << AbstractPattern::separator << "+"  << end << std::endl;
    if (std::string(1, *tmp) != separator || separator == "")
      return false;
    // Skip whitespaces
    AbstractPattern::skipWhitespacesCharacters(tmpRange);
    tmp++;
    std::cout << *tmp << " frfx" << std::endl;
    if (*tmp == '\'' || *tmp == '\"') {
      auto quoteIndex = std::find(tmp, range.second, *tmp);
      func(std::pair<int, int>(tmp - range.first, quoteIndex - range.first));
      range.first = quoteIndex + 1;
      return true;
    }
  }

  return false;
}
