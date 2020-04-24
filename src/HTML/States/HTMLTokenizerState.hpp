#ifndef __HTML_TOKENIZER_STATE__
#define __HTML_TOKENIZER_STATE__

#include <iostream>
#include <memory>
#include <tuple>
#include <vector>
#include <functional>
#include "../HTMLTokenizer.hpp"

/**
 *  Basic HTML tokens datatypes
 */
enum class HTMLTagType {
  DATA, PLAIN_TEXT, RAW_TEXT, RC_DATA, SCRIPT_DATA
};
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
   *  Provides instance of the context
   */
  using TokenizerInstanceProvider = std::function<HTMLTokenizerContext&(void)>;
  /**
   * Base functions
   */
  using NextStateFunctions = std::function<HTMLTokenizerContext&(void)>;

  /**
   * Navigate FSM to the next state
   */
  virtual void next(const std::string& str, const NextStateFunctions& functions) = 0;

  virtual ~HTMLTokenizerState() {};
};

#endif
