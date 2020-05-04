#include "Comment.hpp"

std::vector<std::string> Comment::separators = { "//", "/*", "<!--" };

bool Comment::consume(const Range& range, const EmitFunction& func) const {
  std::string buffer = AbstractPattern::prefix(range);
  if (buffer != "") {
    auto result = std::search(range.first, range.second, this -> end.begin(), this -> end.end());
    range.first = result == range.second ? range.second : result + this -> end.size();
  }
  return buffer == "";
}
