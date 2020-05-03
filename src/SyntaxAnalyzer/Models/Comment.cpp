#include "Comment.hpp"

std::vector<std::string> Comment::separators = { "//", "/*", "<!--" };

bool Comment::consume(const Range& range, const EmitFunction& func) const {
  std::string buffer = AbstractPattern::prefix(range);

  if (buffer != "") {
    auto result = std::find(range.first, range.second, this -> end);
    range.first = result == range.second ? range.second : result + this -> end.size();
  }
  return buffer == "";
}
