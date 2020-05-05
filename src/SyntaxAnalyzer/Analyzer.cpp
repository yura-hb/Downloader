#include "Analyzer.hpp"

std::vector<Reference> Analyzer::loadReferences(const std::string& str) const {
  auto begin = str.begin();
  auto end = str.end();

  std::vector<Reference> result = {};

  AbstractPattern::Range range(begin, end);
  AbstractPattern::EmitFunction function = std::function<void(AbstractPattern::IndexRange)>(
    [&]( const AbstractPattern::IndexRange& relIndexRange) {
    result.push_back(Reference(std::string(range.first + relIndexRange.first, range.first + relIndexRange.second)));
  });

  while (range.first != range.second) {
    for (const auto& pattern : patterns) {
      // Each pattern is a small FCM, if FCM succeds, skip the iteration
      if (pattern -> consume(range, function))
        break;
    }
    range.first++;
  }
  return result;
}

std::string Analyzer::convertToLocalReferences(std::string& str, const std::vector<Reference>& references) const {
  return "";
}
