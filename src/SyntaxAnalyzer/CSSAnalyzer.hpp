#ifndef __CSS_ANALYZER__
#define __CSS_ANALYZER__

#include "Analyzer.hpp"

class CSSAnalyzer: public Analyzer {
  public:
    CSSAnalyzer() : Analyzer({
      std::make_shared<BeginEndAttribute>("url(", "", ")", true),
      std::make_shared<Comment>("//", "", "\n"),
      std::make_shared<Comment>("/*", "", "*/")
    }) {}
};

#endif
