#ifndef __HTML_ANALYZER__
#define __HTML_ANALYZER__

#include <iostream>
#include "Analyzer.hpp"

class HTMLAnalyzer: public Analyzer {
  public:
    HTMLAnalyzer(): Analyzer({
      std::make_shared<Attribute>("href", "=", ""),
      std::make_shared<Attribute>("src", "=", ""),
      std::make_shared<Comment>("<!--", "", "-->")
    }) {}
};


#endif
