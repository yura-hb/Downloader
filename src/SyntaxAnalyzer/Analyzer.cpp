#include "Analyzer.hpp"

std::vector<Reference> Analyzer::loadReferences(const std::string& str) const {
  auto begin = str.begin();
  auto end = str.end();

  AbstractPattern::EmitFunction function = std::function<void(AbstractPattern::IndexRange)>([begin](const AbstractPattern::IndexRange& range) {
    std::cout << std::string(begin + range.first, begin + range.second);
  });


  while (begin != end) {
    for (const auto& pattern : patterns) {
      // Each pattern is a small FCM, if FCM succeds, skip the iteration
      if (pattern -> consume(AbstractPattern::Range(begin, end), function))
        break;
    }
    begin++;
  }
}

std::string Analyzer::convertToLocalReferences(std::string& str, const std::vector<Reference>& references) const {

}
