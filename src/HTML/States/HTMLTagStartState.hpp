#ifndef __HTML_TAG_START_STATE_HPP__
#define __HTML_TAG_START_STATE_HPP__

#include <string>

#include "HTMLTokenizerState.hpp"
#include "HTMLDoctypeState.hpp"
//#include "HTMLTagNameState.hpp"
#include "../HTMLToken.hpp"

/**
 *  Group, which handles implementation of the base tag start states, for solution reference use
 *
 *  https://html.spec.whatwg.org/multipage/parsing.html#end-tag-open-state
 */
struct HTMLTagStartState: public HTMLTokenizerState {
  public:
    enum class State {
      STATE_DATA, LESS_THAN_SIGN, TAG_OPEN_STATE, END_TAG_OPEN_STATE, MARKUP_DECLARATION
    };

    HTMLTagStartState() = delete;
    HTMLTagStartState(State state, HTMLTagType type): state(state), type(type) {}

    void next(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions) override;

  private:
    State state;
    HTMLTagType type;
    /**
     * Basic iteration till the '<' sign with handling of the character reference with &
     *
     * Cases 12.2.5.1 - 12.2.5.5
     */
    void dataStateAction(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions);
    /**
     * Basic action on the '<' sign
     *
     * Cases 12.2.5.9, 12.2.5.12, 12.2.5.15
     */
    void lessThanSignStateAction(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions);
    /**
     * Basic action on the tag open state
     *
     * Case 12.2.5.6
     */
    void tagOpenStateAction(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions);
    /**
     *  Handle end tag open state
     *
     *  Cases 12.2.5.7, 12.2.5.10, 12.2.5.13, 12.2.5.16
     */
    void endTagOpenStateAction(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions);
    /**
     *  Handles markup state for the html and others
     */
    void markupDeclarationStateAction(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions);
    // Helpers
    void reset(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions);
};

#endif
