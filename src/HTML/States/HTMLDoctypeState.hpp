#ifndef __HTML_DOCTYPE_STATE__
#define __HTML_DOCTYPE_STATE__

#include "HTMLTokenizerState.hpp"
#include "HTMLTagStartState.hpp"
#include "HTMLTagAttributesState.hpp"
#include "../HTMLTokenizerContext.hpp"
/**
 *  Group, which handles logic for parsing doctype comment
 *
 *  https://html.spec.whatwg.org/multipage/parsing.html#before-attribute-name-state
 *
 *  Cases 12.2.5.53-12.2.5.68
 */
struct HTMLDoctypeState: public HTMLTokenizerState {
  public:
    enum class State {
      DOCTYPE_STATE,
      BEFORE_DOCTYPE_NAME_STATE,
      DOCTYPE_NAME_STATE,
      AFTER_DOCTYPE_NAME_STATE,
      AFTER_DOCTYPE_PUBLIC_KEYWORD_STATE,
      BEFORE_DOCTYPE_PUBLIC_IDENTIFIER_STATE,
      DOCTYPE_PUBLIC_IDENTIFIER_QUOTED_STATE, // Merge of the single quoted and double quouted state
      AFTER_DOCTYPE_PUBLIC_IDENTIFIER_STATE,
      BETWEEN_DOCTYPE_PUBLIC_AND_SYSTEM_IDENTIFIER_STATE,
      AFTER_DOCTYPE_SYSTEM_KEYWORD_STATE,
      BEFORE_DOCTYPE_SYSTEM_IDENTIFIER_STATE,
      DOCTYPE_SYSTEM_IDENTIFIER_STATE, // Merge of the single quoted and double quoted state
      AFTER_DOCTYPE_SYSTEM_IDENTIFIER_STATE,
      BOGUS_DOCTYPE_STATE
    };

    HTMLDoctypeState() = delete;
    HTMLDoctypeState(State state): state(state) {}

    void next(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions) override;
  private:
    State state;

    void doctypeNameAction(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions);
    void doctypeStartAction(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions);
};

#endif
