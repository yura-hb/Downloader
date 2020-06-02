#include "Analyzer.hpp"

std::vector<std::string> Analyzer::loadReferences(const LocalReference& str) const {
  if (str.isDirectory())
    throw Exception("Can't work with directories");

  std::ifstream in(str.getPath(), std::ios::in);

  if (in.bad())
    throw Exception("Can't read the file");

  Data<> buffer;
  std::vector<std::string> result;

  AbstractPattern::EmitFunction function = std::function<void(const Data<>&)>([&](const Data<>& str) {
    result.push_back(str.stringRepresentation());
  });

  while (in.good() || !buffer.empty()) {
    for (const auto& pattern : patterns) {
      if (pattern -> consume({in, buffer}, function)) {
        buffer = {};
        break;
      }
    }
    buffer.popFirst();
  }

  return result;
}

bool Analyzer::overwriteReferences(const LocalReference& file,
                                   const LocalReference& outputFile,
                                   const std::function<Data<>(Data<>)>& convertReferenceFunctor) const {

  if (file.isDirectory() || outputFile.isDirectory())
    throw Exception("Can't work with the directories");

  if (file.getPath() == outputFile.getPath())
    throw Exception("In and out references are equal, can't continue");

  std::ifstream in(file.getPath(), std::ios::in);

  if (in.bad())
    throw Exception("Can't read the file");

  std::ofstream out(outputFile.getPath(), std::ios::out | std::ios::trunc);

  if (out.bad())
    throw Exception("Can't open file to write");

  Data<> buffer;
  Data<> tmpReference, reference;

  AbstractPattern::EmitFunction function = std::function<void(const Data<>&)>([&](const Data<>& str) {
    tmpReference = str;
    reference = convertReferenceFunctor(str);
  });

  while ((in.good() && out.good()) || !buffer.empty()) {
    for (const auto& pattern : patterns) {
      if (pattern -> consume({in, buffer}, function) && !reference.empty()) {
        buffer.replace(tmpReference, reference);

        if (!buffer.write(out, buffer.begin(), buffer.end()))
          return false;

        buffer = {};
        tmpReference = {};
        reference = {};
        break;
      }
    }

    if (!buffer.empty()) {
      buffer.write(out, buffer.begin(), ++buffer.begin());
      buffer.popFirst();
    }
  }

  return out.good();
}
