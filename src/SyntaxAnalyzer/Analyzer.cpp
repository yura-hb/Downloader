#include "Analyzer.hpp"

std::vector<std::string> Analyzer::loadReferences(const LocalReference& str) const {
  if (str.isDirectory())
    throw Exception("Can't work with directories");

  std::ifstream in(str.getPath(), std::ios::in);

  if (in.bad())
    throw Exception("Can't read the file");

  Data<> buffer;
  std::vector<std::string> result;

  AbstractPattern::EmitFunction function = std::function<void(std::string)>([&](const std::string& str) {
    result.push_back(str);
  });

  while (in.good() || !buffer.empty()) {
    for (const auto& pattern : patterns) {
      if (pattern -> consume({in, buffer}, function))
        break;
    }
    buffer.popFirst();
  }

  return result;
}
