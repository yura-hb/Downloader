#ifndef __HTML_TOKENIZER_STATE__
#define __HTML_TOKENIZER_STATE__

#include <iostream>
#include <memory>
#include <tuple>
#include <vector>
#include <functional>
#include "../HTMLToken.hpp"

/**
 *  Group of whitespace characters
 */
const std::vector<char> whitespaceCharacters = { ' ', '\t', 10, 12 };

/**
 *  Abstract class of the Tokenizer State
 *
 *  The states are taken from HTML parse guide https://html.spec.whatwg.org/multipage/parsing.html.
 *  Implementation tries to group states to reduce amount of models.
 *
 *  Implements one method: `void next(const std::string& str, NextStateFunctions functions)`, where
 *    @param[in] - str, is character or sequence of bytes
 *    @param[in] - NextStateFunctions is a tuple of functions.
 *      0 - Next state provider
 *      1 - Emit token function
 *      2 - Reconsume state provider
 */
struct HTMLTokenizerState {
  /**
   * Returns the next state of the FSM
   */
  using NextStateCompletion = std::function<void(std::shared_ptr<HTMLTokenizerState>)>;
  /**
   * Emits token to the FSM. Can be any type of HTMLToken
   */
  using EmitTokenCompletion = std::function<void(std::unique_ptr<HTMLToken>)>;
  /**
   * Tells tokenizer to reconsume the next state. Means, that the FSM will change its state, but wouldn't move index.
   */
  using ReconsumeStateCompletion = std::function<void(bool)>;
  /**
   * Base functions
   */
  using NextStateFunctions = std::tuple<NextStateCompletion, EmitTokenCompletion, ReconsumeStateCompletion>;

  /**
   * Navigate FSM to the next state
   */
  virtual void next(const std::string& str, const NextStateFunctions& functions) = 0;

  virtual ~HTMLTokenizerState() {};
};

#endif
