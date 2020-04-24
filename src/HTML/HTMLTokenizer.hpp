#ifndef __HTML_TOKENIZER__HPP__
#define __HTML_TOKENIZER__HPP__

#include <iostream>
#include <string>
#include "States/HTMLTagStartState.hpp"
#include "HTMLTokenizerContext.hpp"

class HTMLTokenizer {
  public:
    /**
     * This method simply parsers the data objects
     */
    void parse(const std::string& str);
  private:
    HTMLTokenizerContext context;
};

#endif
