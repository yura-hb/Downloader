#ifndef __HTML_TAG_START_STATE_HPP__
#define __HTML_TAG_START_STATE_HPP__

#include "HTMLTokenizerState.hpp"
#include "HTMLTagNameState.hpp"

 enum class HTMLTagType {
  DATA, PLAIN_TEXT, RAW_TEXT, RC_DATA, SCRIPT_DATA
};

/**
 *  Group, which handles implementation of the base tag start states, for solution reference use
 *
 *  https://html.spec.whatwg.org/multipage/parsing.html#end-tag-open-state
 */
struct HTMLTagStartState: public HTMLTokenizerState {
  public:
    enum class State {
      STATE_DATA, LESS_THAN_SIGN, TAG_OPEN_STATE, END_TAG_OPEN_STATE
    };

    HTMLTagStartState() = delete;
    HTMLTagStartState(State state, HTMLTagType type): state(state), type(type) {}

    void next(const std::string& str, const NextStateFunctions& functions) override;

  private:
    State state;
    HTMLTagType type;
    /**
     * Basic iteration till the '<' sign with handling of the character reference with &
     *
     * Cases 12.2.5.1 - 12.2.5.5
     */
    void dataStateAction(const std::string& str, const NextStateFunctions& functions);
    /**
     * Basic action on the '<' sign
     *
     * Cases 12.2.5.9, 12.2.5.12, 12.2.5.15
     */
    void lessThanSignStateAction(const std::string& str, const NextStateFunctions& functions);
    /**
     * Basic action on the tag open state
     *
     * Case 12.2.5.6
     */
    void tagOpenStateAction(const std::string& str, const NextStateFunctions& functions);
    /**
     *  Handle end tag open state
     *
     *  Cases 12.2.5.7, 12.2.5.10, 12.2.5.13, 12.2.5.16
     */
    void endTagOpenStateAction(const std::string& str, const NextStateFunctions& functions);

    // Helpers
    void reset(const std::string& str, const NextStateFunctions& functions);
};

#endif
