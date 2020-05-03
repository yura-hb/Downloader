#ifndef __CSS_ANALYZER__
#define __CSS_ANALYZER__

#include "Analyzer.hpp"

class CSSAnalyzer: public Analyzer {
  CSSAnalyzer() : Analyzer({
    std::make_shared<Attribute>("url(", "", ")"),
    std::make_shared<Comment>("//", "", "\n"),
    std::make_shared<Comment>("/*", "", "*/")
  }) {}
};

#endif
