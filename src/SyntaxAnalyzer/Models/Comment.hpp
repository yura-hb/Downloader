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
    Comment(const std::string& begin, const std::string& separator, const std::string& end): AbstractPattern(begin, separator, end) {}

    bool consume(const Range& range, const EmitFunction& func) const override;
  private:
    static std::vector<std::string> separators;
};

#endif
