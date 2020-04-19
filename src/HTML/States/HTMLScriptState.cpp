#include "HTMLScriptState.hpp"

using State = HTMLScriptState::State;

void HTMLScriptState::next(const std::string& str, const NextStateFunctions& functions) {
  switch (state) {
  case (State::SCRIPT_DATA_ESCAPE_START_STATE):
  case (State::SCRIPT_DATA_ESCAPE_START_DASH_STATE):
    scriptDataEscapeStartStateAction(str, functions);
    break;
  case (State::SCRIPT_DATA_ESCAPE_STATE):
  case (State::SCRIPT_DATA_ESCAPE_DASH_STATE):
  case (State::SCRIPT_DATA_ESCAPE_DASH_DASH_STATE):
    scriptDataEscapeStateAction(str, functions);
    break;
  case (State::SCRIPT_DATA_ESCAPE_LESS_THAN_SIGN_STATE):
  case (State::SCRIPT_DATA_DOUBLE_ESCAPE_LESS_THAN_SIGN_STATE):
    lessThanSignStateAction(str, functions);
    break;
  case (State::SCRIPT_DATA_ESCAPE_END_TAG_OPEN_STATE):
    endTagNameStateAction(str, functions);
    break;
  case (State::SCRIPT_DATA_DOUBLE_ESCAPE_END_STATE):
    doubleEscapeStartStateAction(str, functions);
    break;
  case (State::SCRIPT_DATA_DOUBLE_ESCAPE_STATE):
  case (State::SCRIPT_DATA_DOUBLE_ESCAPE_DASH_STATE):
  case (State::SCRIPT_DATA_DOUBLE_ESCAPE_DASH_DASH_STATE):
    doubleEscapeStateAction(str, functions);
    break;
  }
}
// READY
void HTMLScriptState::scriptDataEscapeStartStateAction(const std::string& str, const NextStateFunctions& functions) {
  if (str[0] == '-') {
    // Emit a U+002D HYPHEN-MINUS character token
    state = state == State::SCRIPT_DATA_ESCAPE_START_STATE ? State::SCRIPT_DATA_ESCAPE_START_DASH_STATE : State::SCRIPT_DATA_ESCAPE_DASH_DASH_STATE;
    return;
  }

  std::get<0>(functions)(std::make_shared<HTMLTagStartState>(HTMLTagStartState::State::STATE_DATA, HTMLTagType::SCRIPT_DATA));
  std::get<2>(functions)(true);
}

// READY
void HTMLScriptState::scriptDataEscapeStateAction(const std::string& str, const NextStateFunctions& functions) {
  if (str[0] == '-') {
    // Emit a U+002D HYPHEN-MINUS character token
    if (state != State::SCRIPT_DATA_ESCAPE_DASH_DASH_STATE)
      state = state == State::SCRIPT_DATA_ESCAPE_STATE ? State::SCRIPT_DATA_ESCAPE_DASH_STATE : State::SCRIPT_DATA_ESCAPE_DASH_DASH_STATE;
    return;
  }

  if (str[0] == '<') {
    state = State::SCRIPT_DATA_ESCAPE_LESS_THAN_SIGN_STATE;
    return;
  }

  if (str[0] == '>' && state == State::SCRIPT_DATA_ESCAPE_DASH_DASH_STATE) {
    // Switch to the script data state. Emit a U+003E GREATER-THAN SIGN character token.
    std::get<0>(functions)(std::make_shared<HTMLTagStartState>(HTMLTagStartState::State::STATE_DATA, HTMLTagType::SCRIPT_DATA));
    return;
  }

  // U+0000 NULL
  // This is an unexpected-null-character parse error. Emit a U+FFFD REPLACEMENT CHARACTER character token.
  //

  if (state == State::SCRIPT_DATA_ESCAPE_DASH_STATE || state == State::SCRIPT_DATA_ESCAPE_DASH_DASH_STATE ) {
    state = State::SCRIPT_DATA_ESCAPE_STATE;
  }

  // Emit the current input character as a character token.
}
// READY
void HTMLScriptState::lessThanSignStateAction(const std::string& str, const NextStateFunctions& functions) {
  if (str[0] == '/') {
    // Set the temporary buffer to the empty string
    state = state == State::SCRIPT_DATA_DOUBLE_ESCAPE_LESS_THAN_SIGN_STATE ? State::SCRIPT_DATA_DOUBLE_ESCAPE_END_STATE : State::SCRIPT_DATA_ESCAPE_END_TAG_OPEN_STATE;
    return;
  }

  if (std::isalpha(str[0]) && state == State::SCRIPT_DATA_ESCAPE_LESS_THAN_SIGN_STATE) {
    // Set the temporary buffer to the empty string. Emit a U+003C LESS-THAN SIGN character token
    state = State::SCRIPT_DATA_DOUBLE_ESCAPE_START_STATE;
    std::get<2>(functions)(true);
  }

  // Emit a U+003C LESS-THAN SIGN character token. Reconsume in the script data escaped state.
  state = state == State::SCRIPT_DATA_DOUBLE_ESCAPE_LESS_THAN_SIGN_STATE ? State::SCRIPT_DATA_DOUBLE_ESCAPE_STATE : State::SCRIPT_DATA_ESCAPE_STATE;
  std::get<2>(functions)(true);
}
// READDY
void HTMLScriptState::endTagOpenStateAction(const std::string& str, const NextStateFunctions& functions) {
  if (std::isalpha(str[0])) {
    // Set the temporary buffer to the empty string. Emit a U+003C LESS-THAN SIGN character token
    state = State::SCRIPT_DATA_ESCAPE_END_TAG_NAME_STATE;
    std::get<2>(functions)(true);
  }

  // Emit a U+003C LESS-THAN SIGN character token and a U+002F SOLIDUS character token. Reconsume in the script data escaped state
  state = State::SCRIPT_DATA_ESCAPE_STATE;
  std::get<2>(functions)(true);
}
// Ready
void HTMLScriptState::endTagNameStateAction(const std::string& str, const NextStateFunctions& functions) {
  if (std::find(whitespaceCharacters.begin(), whitespaceCharacters.end(), str[0]) != whitespaceCharacters.end()) {
    //  If the current end tag token is an appropriate end tag token, then switch to the before attribute name state.
    //  Otherwise, treat it as per the "anything else" entry below.
    std::get<0>(functions)(std::make_shared<HTMLTagAttributesState>(HTMLTagAttributesState::State::BEFORE_ATTRIBUTE_NAME));
    return;
  }

  if (str[0] == '/') {
    // If the current end tag token is an appropriate end tag token, then switch to the self-closing start tag state. Otherwise, treat it as per the "anything else" entry below.
    return;
  }

  if (str[0] == '>') {
    //If the current end tag token is an appropriate end tag token, then switch to the data state and emit the current tag token.
    // Otherwise, treat it as per the "anything else" entry below.
    std::get<0>(functions)(std::make_shared<HTMLTagStartState>(HTMLTagStartState::State::STATE_DATA, HTMLTagType::DATA));
    return;
  }

  if (std::isalpha(str[0])) {
    char tmp = std::tolower(str[0]);

    // Append the current input character to the temporary buffer.
    return;
  }

  // Emit a U+003C LESS-THAN SIGN character token, a U+002F SOLIDUS character token, and a character token for each of the characters in the temporary buffer (in the order they were added to the buffer).
  // Reconsume in the script data escaped state.

  state = State::SCRIPT_DATA_ESCAPE_STATE;
  std::get<2>(functions)(true);
}

// READY
void HTMLScriptState::doubleEscapeStartStateAction(const std::string& str, const NextStateFunctions& functions) {
  if (std::find(whitespaceCharacters.begin(), whitespaceCharacters.end(), str[0]) != whitespaceCharacters.end() ||
      str[0] == '/' ||
      str[0] == '>') {
    //  If the temporary buffer is the string "script", then switch to the script data double escaped state.
    // Otherwise, switch to the script data escaped state. Emit the current input character as a character token.

    return;
  }

  if (std::isalpha(str[0])) {
    char tmp = std::tolower(str[0]);

    // Append the current input character to the temporary buffer. Emit the current input character as a character token.
    return;
  }

  state = state == State::SCRIPT_DATA_DOUBLE_ESCAPE_END_STATE ? State::SCRIPT_DATA_DOUBLE_ESCAPE_STATE : State::SCRIPT_DATA_ESCAPE_STATE;
  std::get<2>(functions)(true);
}

// READY
void HTMLScriptState::doubleEscapeStateAction(const std::string& str, const NextStateFunctions& functions) {
  if (str[0] == '-') {
    //  Emit a U+002D HYPHEN-MINUS character token.
    if (state != State::SCRIPT_DATA_DOUBLE_ESCAPE_DASH_STATE)
      state = state == State::SCRIPT_DATA_DOUBLE_ESCAPE_STATE ? State::SCRIPT_DATA_DOUBLE_ESCAPE_DASH_STATE : State::SCRIPT_DATA_DOUBLE_ESCAPE_DASH_DASH_STATE;
    return;
  }

  if (str[0] == '<') {
    // Emit a U+003C LESS-THAN SIGN character token.
    state = State::SCRIPT_DATA_DOUBLE_ESCAPE_LESS_THAN_SIGN_STATE;
    return;
  }

  if (state == State::SCRIPT_DATA_DOUBLE_ESCAPE_DASH_STATE) {
    state = State::SCRIPT_DATA_DOUBLE_ESCAPE_STATE;
    return;
  }

  if (str[0] == '>' && state == State::SCRIPT_DATA_DOUBLE_ESCAPE_DASH_DASH_STATE) {
    // Switch to the script data state. Emit a U+003E GREATER-THAN SIGN character token.
    std::get<0>(functions)(std::make_shared<HTMLTagStartState>(HTMLTagStartState::State::STATE_DATA, HTMLTagType::SCRIPT_DATA));
    return;
  }

  state = State::SCRIPT_DATA_DOUBLE_ESCAPE_STATE;

  // Emit the current input character as a character token.
}
