#include "Attribute.hpp"

const std::vector<char> Attribute::whitespaces = { '\n', ' ', '\t', 12 };

bool Attribute::consume(const Input& input, const EmitFunction& func) const {
  if (!AbstractPattern::validateBegin(input))
    return false;

  std::string quoteSeparator = "";

  if (!readUntilSeparator(input) ||
      !input.first.good() ||
      !readUntilQuote(input, true, quoteSeparator) ||
      !input.first.good() ||
      !readUntilQuote(input, false, quoteSeparator))
    return false;

  auto linkBegin = input.second.find(quoteSeparator, input.second.begin(), true);

  func(input.second.subsequence(linkBegin, --input.second.end()));

  input.second = {};

  return true;
}

bool Attribute::readUntilSeparator(const Input& input) const {
  if (input.second.endsWith(separator))
    return true;

  while (input.first.good()) {
    input.second.read(input.first, 1);

    if (input.second.endsWith(separator))
      break;

    if (std::find(whitespaces.begin(), whitespaces.end(), *(input.second.end()--)) == whitespaces.end())
      return false;
  }
  return true;
}

bool Attribute::readUntilQuote(const Input& input, bool isInitial, std::string& quote) const {
  std::string singleQuote = "'", doubleQuote = "\"";

  while (input.first.good()) {
    input.second.read(input.first, 1);

    if ((isInitial || quote == singleQuote) && input.second.endsWith(singleQuote) ) {
      quote = singleQuote;
      break;
    }

    if ((isInitial || quote == doubleQuote) && input.second.endsWith(doubleQuote) ) {
      quote = doubleQuote;
      break;
    }


    if (isInitial && std::find(whitespaces.begin(), whitespaces.end(), *(input.second.end()--)) == whitespaces.end())
      return false;
  }

  return true;
}
