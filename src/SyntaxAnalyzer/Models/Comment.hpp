#ifndef __COMMENTS__
#define __COMMENTS__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "AbstractPattern.hpp"

struct Comment: public AbstractPattern {
  public:
    Comment(const std::string& begin,
            const std::string& separator,
            const std::string& end): AbstractPattern(begin, separator, end) {}

    bool consume(const Input& input, const EmitFunction& func) const override;
};

#endif
