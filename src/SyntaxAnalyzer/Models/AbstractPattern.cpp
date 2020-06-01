#include "AbstractPattern.hpp"

bool AbstractPattern::validateBegin(const Input& input) const {
  if (input.second.size() < begin.size())
    input.second.read(input.first, begin.size() - input.second.size());

  if (input.second.size() < begin.size() || !input.second.beginsWith(begin))
    return false;

  return true;
}
