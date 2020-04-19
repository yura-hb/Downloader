#ifndef __HTML_COMMENT_STATE__
#define __HTML_COMMENT_STATE__

#include "HTMLTokenizerState.hpp"
#include "HTMLTagStartState.hpp"
/**
 *  Group, which handles logic for parsing comments
 *
 *  https://html.spec.whatwg.org/multipage/parsing.html#before-attribute-name-state
 *
 *  Cases 12.2.5.41, 12.2.5.43 - 12.2.5.52
 */
struct HTMLCommentState: public HTMLTokenizerState {
  public:
    enum class State {
      BOGUS_COMMENT,
      COMMENT_START_STATE,
      COMMENT_START_DASH_STATE,
      COMMENT_STATE,
      COMMENT_LESS_THAN_SIGN_STATE,
      COMMENT_LESS_THAN_SIGN_BANG_STATE,
      COMMENT_LESS_THAN_SIGN_BANG_DASH_STATE,
      COMMENT_LESS_THAN_SIGN_BANG_DASH_DASH_STATE,
      COMMENT_END_DASH_STATE,
      COMMENT_END_STATE,
      COMMENT_END_BANG_STATE
    };

    HTMLCommentState() = delete;
    HTMLCommentState(State state): state(state) {}

    void next(const std::string& str, const NextStateFunctions& functions) override;
  private:
    State state;


    // Helpers
    void switchToDataState(const NextStateFunctions& functions);
    void reconsumeInCommentState(const NextStateFunctions& functions);
};

#endif
