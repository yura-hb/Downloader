#ifndef __HTML_TOKENIZER__
#define __HTML_TOKENIZER__

#include <iostream>
#include <string>

class HTMLTokenizer {
  public:
    static std::string replacementCharacterToken;

    void setup(const std::string& str);

  private:

    void consume();
};

#endif
