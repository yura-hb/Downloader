#ifndef __HTML_ANALYZER__
#define __HTML_ANALYZER__

#include <iostream>
#include "Analyzer.hpp"

class HTMLAnalyzer: public Analyzer {
  public:
    HTMLAnalyzer(): Analyzer(std::vector<std::shared_ptr<AbstractPattern>> {
      std::make_shared<HTMLAttribute>("href", "=", ""),
      std::make_shared<Attribute>("src", "=", ""),
      std::make_shared<Comment>("<!--", "", "-->")
    }) {}
};
#endif
