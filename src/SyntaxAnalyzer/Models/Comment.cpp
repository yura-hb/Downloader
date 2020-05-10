#include "Comment.hpp"

bool Comment::consume(const Input& input, const EmitFunction& func) const {
  if (input.second.size() < begin.size())
    input.second.read(input.first, begin.size() - input.second.size());

  if (input.second.size() < begin.size() || !input.second.beginsWith(begin))
    return false;

  input.second.readUntil(input.first, end);

  if (input.first.eof())
    return false;

  input.second = {};

  return true;
}
