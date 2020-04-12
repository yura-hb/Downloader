#ifndef __HTML_TAG_ATTRIBUTES_STATE__
#define __HTML_TAG_ATTRIBUTES_STATE__

#include "HTMLTokenizerState.hpp"
#include "HTMLTagStartState.hpp"
/**
 *  Group, which handles logic for parsing attributes and values of specific tags
 *
 *  https://html.spec.whatwg.org/multipage/parsing.html#before-attribute-name-state
 *
 *  Cases 12.2.5.32 - 12.2.5.39
 */
struct HTMLTagAttributesState: public HTMLTokenizerState {
  public:
    enum class State {
      BEFORE_ATTRIBUTE_NAME, ATTRIBUTE_NAME_STATE, AFTER_ATTRIBUTE_NAME_STATE, BEFORE_ATTRIBUTE_VALUE_STATE,
      BEFORE_ATTRIBUTE_VALUE_QUOTED_STATE, // Merge of double quoted and single quoted state
      ATTRIBUTE_VALUE_UNQUOTED_STATE, AFTER_ATTRIBUTE_VALUE_QUOTED_STATE
    };

    HTMLTagAttributesState(State state): state(state) {}

    void next(const std::string& str, const NextStateFunctions& functions) override;
  private:

    State state;
};

#endif
