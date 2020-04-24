#ifndef __HTML_TOKENIZER_CONTEXT_HPP__
#define __HTML_TOKENIZER_CONTEXT_HPP__

#include <iostream>
#include <memory>
#include <vector>
#include "States/HTMLTokenizerState.hpp"
#include "HTMLToken.hpp"
//#include "HTMLTokenizer.hpp"

class HTMLTokenizer;
struct HTMLTokenizerState;
/**
 *  During the tokenization there is high demand on caching structures,
 *  emition of the tokens and communication between tokenizer and the states.
 *
 *  The context is the object, which will see any State and can modify it.
 */
class HTMLTokenizerContext {
  public:
    // Weak pointer to current tokenizer instance
    //std::shared_ptr<HTMLTokenizer> tokenizer;
    //  - Setters
    void setState(std::shared_ptr<HTMLTokenizerState> state);
    void setReconsumeState();
    void setToken(std::shared_ptr<HTMLToken> token);
    void addToBuffer(const std::string& str);
    /**
     *  Invalidates temporary flags from the context
     */
    void prepareForNextState();
    /**
     * Emit current token to the tree constructor
     */
    void emit(const std::shared_ptr<HTMLToken> token);
    /**
     *  Emits local token, which is set in context
     */
    void emitLocalToken();
    /**
     *  Loads n characters from the stream
     */
    std::string substring(const size_t length) const;
    //  - Getters
    std::shared_ptr<HTMLTokenizerState>& getState();
    std::shared_ptr<HTMLToken>& getCurrentToken();
    std::string getBuffer();
    bool getReconsumeState() const;
  private:
    /**
     *  Current state of the tokenizer
     */
    std::shared_ptr<HTMLTokenizerState> state;
    /**
     *  Temporary buffer needed for the operations
     */
    std::string buffer;
    /**
     *  Temporary token to store
     */
    std::shared_ptr<HTMLToken> token;
    /**
     * Boolean flag, which shows the tokenizer, if it should move to the next index or stay on the same
     */
    bool shouldReconsume = false;
};
#endif
