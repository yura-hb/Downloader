#include "HTMLCommentState.hpp"

using State = HTMLCommentState::State;

void HTMLCommentState::next(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions) {
  switch (state) {
  case State::BOGUS_COMMENT:
    if (str[0] == '>') {
      switchToDataState(functions);
      return;
    }
  case State::COMMENT_START_STATE:
    if (str[0] == '-') {
      state = State::COMMENT_START_DASH_STATE;
      return;
    }

    if (str[0] == '>') {
      switchToDataState(functions);
      return;
    }

    reconsumeInCommentState(functions);

  case State::COMMENT_START_DASH_STATE:
    if (str[0] == '-') {
      state = State::COMMENT_END_STATE;
      return;
    }

    if (str[0] == '>') {
      switchToDataState(functions);
      return;
    }

    // Append a U+002D HYPHEN-MINUS character (-) to the comment token's data. Reconsume in the comment state.
    reconsumeInCommentState(functions);


  case State::COMMENT_STATE:
    if (str[0] == '<') {
      state = State::COMMENT_LESS_THAN_SIGN_STATE;
      return;
    }

    if (str[0] == '-') {
      state = State::COMMENT_END_DASH_STATE;
      return;
    }

    //U+0000 NULL
    //  This is an unexpected-null-character parse error. Append a U+FFFD REPLACEMENT CHARACTER character to the comment token's data.
    //

    // Append the current input character to the comment token's data.

  case State::COMMENT_LESS_THAN_SIGN_STATE:
    if (str[0] == '!') {
      // Append the current input character to the comment token's data. Switch to the comment less-than sign bang state.
      state = State::COMMENT_LESS_THAN_SIGN_BANG_STATE;
      return;
    }

    if (str[0] == '<') {
      // Append the current input character to the comment token's data.
      return;
    }

    reconsumeInCommentState(functions);

  case State::COMMENT_LESS_THAN_SIGN_BANG_STATE:
    if (str[0] == '-') {
      state = State::COMMENT_LESS_THAN_SIGN_BANG_DASH_STATE;
      return;
    }

    reconsumeInCommentState(functions);

  case State::COMMENT_LESS_THAN_SIGN_BANG_DASH_DASH_STATE:
    if (str[0] == '>') {
      state = State::COMMENT_END_STATE;
      std::get<2>(functions)(true);
      return;
    }

    state = State::COMMENT_END_STATE;
    std::get<2>(functions)(true);

  case State::COMMENT_END_DASH_STATE:
    if (str[0] == '-') {
      state = State::COMMENT_END_STATE;
      std::get<2>(functions)(true);
      return;
    }

    // Append a U+002D HYPHEN-MINUS character (-) to the comment token's data. Reconsume in the comment state.
    reconsumeInCommentState(functions);

  case State::COMMENT_END_STATE:
    if (str[0] == '>') {
      switchToDataState(functions);
      return;
    }

    if (str[0] == '!') {
      state = State::COMMENT_END_BANG_STATE;
      return;
    }

    if (str[0] == '-') {
      // Append a U+002D HYPHEN-MINUS character (-) to the comment token's data.
      return;
    }

    // Append two U+002D HYPHEN-MINUS characters (-) to the comment token's data. Reconsume in the comment state
    reconsumeInCommentState(functions);

  case State::COMMENT_END_BANG_STATE:
    if (str[0] == '-') {
      // Append two U+002D HYPHEN-MINUS characters (-) and a U+0021 EXCLAMATION MARK character (!) to the comment token's data.
      state = State::COMMENT_END_DASH_STATE;
      return;
    }

    if (str[0] == '>') {
      switchToDataState(functions);
      return;
    }

    // Append two U+002D HYPHEN-MINUS characters (-) and a U+0021 EXCLAMATION MARK character (!) to the comment token's data. Reconsume in the comment state.
    reconsumeInCommentState(functions);
  }
}

void HTMLCommentState::switchToDataState(const std::function<HTMLTokenizerContext&(void)> functions) {
  std::get<0>(functions)(std::make_shared<HTMLTagStartState>(HTMLTagStartState::State::STATE_DATA, HTMLTagType::DATA));
  // Emit the comment token.
}

void HTMLCommentState::reconsumeInCommentState(const std::function<HTMLTokenizerContext&(void)> functions) {
   state = State::COMMENT_STATE;
   std::get<2>(functions)(true);
}
