#ifndef __COMMENTS__
#define __COMMENTS__

#include <iostream>
#include <vector>
#include <algorithm>
#include "AbstractPattern.hpp"

/**
 * Help model to tell the analyzer, how to react on the specific elements
 */
struct Comment: public AbstractPattern {
  public:
    Comment(std::string begin, std::string end, std::string separator = ""): AbstractPattern(begin, end, separator) {}

    bool consume(const Range& range, const EmitFunction& func) const override;
  private:
    static std::vector<std::string> separators;
};

#endif
