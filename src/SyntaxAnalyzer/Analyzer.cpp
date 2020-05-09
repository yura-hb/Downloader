#include "Analyzer.hpp"

std::vector<std::string> Analyzer::loadReferences(const LocalReference& str) const {
 /* auto begin = str.begin();
  auto end = str.end();

  std::vector<std::string> result = {};

  AbstractPattern::Range range(begin, end);
  AbstractPattern::EmitFunction function = std::function<void(AbstractPattern::IndexRange)>(
    [&]( const AbstractPattern::IndexRange& relIndexRange) {
    result.push_back(std::string(range.first + relIndexRange.first, range.first + relIndexRange.second));
  });

  while (range.first != range.second) {
    for (const auto& pattern : patterns) {
      // Each pattern is a small FCM, if FCM succeds, skip the iteration
      if (pattern -> consume(range, function))
        break;
    }
    range.first++;
  }
  return result;*/
}
