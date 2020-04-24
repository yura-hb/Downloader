#ifndef __HTML_TOKENIZER__HPP__
#define __HTML_TOKENIZER__HPP__

#include <iostream>
#include <string>
#include <memory>
#include "States/HTMLTagStartState.hpp"
#include "HTMLTokenizerContext.hpp"

class HTMLTokenizer: std::enable_shared_from_this<HTMLTokenizer> {
  public:
    /**
     * This method simply parsers the data objects
     */
    void parse(const std::string& str);
    /**
     * Cut part of the text from the string of the specific length, from current parsing index
     */
    std::string substring(size_t length);
  private:
    HTMLTokenizerContext context;
    /**
     * During parsing store current parsing index
     */
    size_t parsingIndex = 0;
    /**
     * Parsing instance reference
     */
    std::shared_ptr<const std::string> parsingDataReference = nullptr;
};

#endif
