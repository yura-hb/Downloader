#include "Analyzer.hpp"

std::vector<Reference> Analyzer::loadReferences(const std::string& str) const {
  auto begin = str.begin();
  auto end = str.end();

  AbstractPattern::Range range(begin, end);
  AbstractPattern::EmitFunction function = std::function<void(AbstractPattern::IndexRange)>(
    [range](const AbstractPattern::IndexRange& relIndexRange) {
    //std::cout << std::string(range.first + relIndexRange.first, range.first + relIndexRange.second) << std::endl;
  });

  while (range.first != range.second) {
    for (const auto& pattern : patterns) {
      // Each pattern is a small FCM, if FCM succeds, skip the iteration
      if (pattern -> consume(range, function))
        break;
    }
    range.first++;
  }
  return {};
}

std::string Analyzer::convertToLocalReferences(std::string& str, const std::vector<Reference>& references) const {
  return "";
}
