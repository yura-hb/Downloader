#ifndef __HTML_SCRIPT_STATE__
#define __HTML_SCRIPT_STATE__

#include "HTMLTokenizerState.hpp"
#include "HTMLTagStartState.hpp"
#include "HTMLTagAttributesState.hpp"
/**
 *  Group, which handles logic for parsing script tag
 *
 *  https://html.spec.whatwg.org/multipage/parsing.html#before-attribute-name-state
 *
 *  Cases 12.2.5.18-12.2.5.31
 */
struct HTMLScriptState: public HTMLTokenizerState {
  public:
    enum class State {
      SCRIPT_DATA_ESCAPE_START_STATE,
      SCRIPT_DATA_ESCAPE_START_DASH_STATE,
      SCRIPT_DATA_ESCAPE_STATE,
      SCRIPT_DATA_ESCAPE_DASH_STATE,
      SCRIPT_DATA_ESCAPE_DASH_DASH_STATE,
      SCRIPT_DATA_ESCAPE_LESS_THAN_SIGN_STATE,
      SCRIPT_DATA_ESCAPE_END_TAG_OPEN_STATE,
      SCRIPT_DATA_ESCAPE_END_TAG_NAME_STATE,
      SCRIPT_DATA_DOUBLE_ESCAPE_START_STATE,
      SCRIPT_DATA_DOUBLE_ESCAPE_STATE,
      SCRIPT_DATA_DOUBLE_ESCAPE_DASH_STATE,
      SCRIPT_DATA_DOUBLE_ESCAPE_DASH_DASH_STATE,
      SCRIPT_DATA_DOUBLE_ESCAPE_LESS_THAN_SIGN_STATE,
      SCRIPT_DATA_DOUBLE_ESCAPE_END_STATE
    };

    HTMLScriptState() = delete;
    HTMLScriptState(State state): state(state) {}

    void next(const std::string& str, const NextStateFunctions& functions) override;
  private:
    State state;

    void scriptDataEscapeStartStateAction(const std::string& str, const NextStateFunctions& functions);
    void scriptDataEscapeStateAction(const std::string& str, const NextStateFunctions& functions);
    void lessThanSignStateAction(const std::string& str, const NextStateFunctions& functions);
    void endTagOpenStateAction(const std::string& str, const NextStateFunctions& functions);
    void endTagNameStateAction(const std::string& str, const NextStateFunctions& functions);
    void doubleEscapeStartStateAction(const std::string& str, const NextStateFunctions& functions);
    void doubleEscapeStateAction(const std::string& str, const NextStateFunctions& functions);
};

#endif
