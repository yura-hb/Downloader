#ifndef __HTML_TOKENIZER_CONTEXT_HPP__
#define __HTML_TOKENIZER_CONTEXT_HPP__

#include <iostream>
#include <memory>
#include <vector>
#include "States/HTMLTokenizerState.hpp"

/**
 *  During the tokenization there is high demand on caching structures,
 *  emition of the tokens and communication between tokenizer and the states.
 *
 *  The context is the object, which will see any State and can modify it.
 */
class HTMLTokenizerContext {
  public:
    //  - Setters
    void setState(std::shared_ptr<HTMLTokenizerState> state) {
      this -> state = state;
    }
    void setReconsumeState() {
      shouldReconsume = true;
    }
    void setToken(std::shared_ptr<HTMLToken> token) {
      this -> token = token;
    }
    /**
     *  Invalidates temporary flags from the context
     */
    void prepareForNextState() {
      shouldReconsume = false;
    }
    /**
     * Emit current token to the tree constructor
     */
    void emit(const std::shared_ptr<HTMLToken> token) {

    }
    /**
     *  Emits local token, which is set in context
     */
    void emitLocalToken() {

    }
    //  - Getters
    std::shared_ptr<HTMLTokenizerState>& getState() {
      return state;
    }
    bool getReconsumeState() const {
      return shouldReconsume;
    }
  private:
    /**
     *  Current state of the tokenizer
     */
    std::shared_ptr<HTMLTokenizerState> state;
    /**
     *  Temporary buffer needed for the operations
     */
    std::vector<std::string> buffer;
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
