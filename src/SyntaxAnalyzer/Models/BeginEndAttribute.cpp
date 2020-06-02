#include "BeginEndAttribute.hpp"

bool BeginEndAttribute::consume(const Input& input, const EmitFunction& func) const {
  if (!AbstractPattern::validateBegin(input))
    return false;

  if (!input.second.readUntil(input.first, end) || !input.first.good())
    return false;

  auto referenceBegin = input.second.find(begin, input.second.begin(), true);
  auto reference = input.second.subsequence(referenceBegin, --input.second.end());

  if (trimQuotes &&
      (*reference.begin() == '\'' || *reference.begin() == '"') &&
      (*(--reference.end()) == '\'' || *(--reference.end()) == '"')) {
    reference.popFirst();
    reference.popLast();
  }

  func(reference);

  return true;
}
