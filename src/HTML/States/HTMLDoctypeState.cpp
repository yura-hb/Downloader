#include "HTMLDoctypeState.hpp"

using State = HTMLDoctypeState::State;

void HTMLDoctypeState::next(const std::string& str, const NextStateFunctions& functions) {
  switch (state) {
  case (State::DOCTYPE_STATE):
  case (State::BEFORE_DOCTYPE_NAME_STATE):
    doctypeStartAction(str, functions);
    break;
  case (State::DOCTYPE_NAME_STATE):
    doctypeNameAction(str, functions);
    break;
  case (State::AFTER_DOCTYPE_NAME_STATE):
    afterDoctypeNameAction(str, functions);
    break;
  case (State::AFTER_DOCTYPE_PUBLIC_KEYWORD_STATE):
  case (State::BEFORE_DOCTYPE_PUBLIC_IDENTIFIER_STATE):
  case (State::DOCTYPE_PUBLIC_IDENTIFIER_QUOTED_STATE)
    doctypePublicKeywordStateAction(str, functions);
    break;

  }
}

void HTMLDoctypeState::doctypeStartAction(const std::string& str, const NextStateFunctions& functions) {
  if (std::find(whitespaceCharacters.begin(), whitespaceCharacters.end(), str[0]) != whitespaceCharacters.end()) {
    if (state == State::DOCTYPE_STATE)
      state = State::BEFORE_DOCTYPE_NAME_STATE;
    return;
  }

  if (std::isupper(str[0]) && state == State::BEFORE_DOCTYPE_NAME_STATE) {
    // Create a new DOCTYPE token.
    // Set the token's name to the lowercase version of the current input character (add 0x0020 to the character's code point).
    // Switch to the DOCTYPE name state.
    state = State::DOCTYPE_NAME_STATE;
    return;
  }

  if (str[0] == '>') {
    // Create a new DOCTYPE token. Set its force-quirks flag to on. Switch to the data state. Emit the token.
    return;
  }

  state = State::DOCTYPE_NAME_STATE;
  // Create a new DOCTYPE token. Set the token's name to the current input character.
}

void HTMLDoctypeState::doctypeNameAction(const std::string& str, const NextStateFunctions& functions) {
  if (std::find(whitespaceCharacters.begin(), whitespaceCharacters.end(), str[0]) != whitespaceCharacters.end()) {
    state = State::AFTER_DOCTYPE_NAME_STATE;
    return;
  }

  if (str[0]== '>') {
    // Switch to the data state. Emit the current DOCTYPE token.

    std::get<0>(functions)(std::make_shared<HTMLTagStartState>(HTMLTagStartState::State::STATE_DATA, HTMLTagType::DATA));
    return;
  }

  if (std::isupper(str[0])) {
    // Append the lowercase version of the current input character
    // (add 0x0020 to the character's code point) to the current DOCTYPE token's name.
    char tmp = std::tolower(str[0]);


  }
  // Append the current input character to the current DOCTYPE token's name.
}

void HTMLDoctypeState::afterDoctypeNameAction(const std::string& str, const NextStateFunctions& functions) {
  if (std::find(whitespaceCharacters.begin(), whitespaceCharacters.end(), str[0]) != whitespaceCharacters.end())
    return;

  if (str[0]== '>') {
    // Switch to the data state. Emit the current DOCTYPE token.

    std::get<0>(functions)(std::make_shared<HTMLTagStartState>(HTMLTagStartState::State::STATE_DATA, HTMLTagType::DATA));
    return;
  }

  if (std::isupper(str[0])) {
    // Append the lowercase version of the current input character
    // (add 0x0020 to the character's code point) to the current DOCTYPE token's name.
    char tmp = std::tolower(str[0]);


  }
  // If the six characters starting from the current input character are an ASCII case-insensitive match for the word "PUBLIC", then consume those characters and switch to the after DOCTYPE public keyword state.

  //Otherwise, if the six characters starting from the current input character are an ASCII case-insensitive match for the word "SYSTEM", then consume those characters and switch to the after DOCTYPE system keyword state.

  //Otherwise, this is an invalid-character-sequence-after-doctype-name parse error. Set the DOCTYPE token's force-quirks flag to on. Reconsume in the bogus DOCTYPE state.
}

void HTMLDoctypeState::doctypePublicKeywordStateAction(const std::string& str, const NextStateFunctions& functions) {
  if (std::find(whitespaceCharacters.begin(), whitespaceCharacters.end(), str[0]) != whitespaceCharacters.end()) {
    state = State::BEFORE_DOCTYPE_PUBLIC_IDENTIFIER_STATE;
    return;
  }

  if (str[0] == '\"' || str[0] == '\'') {
    // Set the DOCTYPE token's public identifier to the empty string (not missing),
    // then switch to the DOCTYPE public identifier (double-quoted) state.
    if (state == State::DOCTYPE_PUBLIC_IDENTIFIER_QUOTED_STATE) {
      state = State::BEFORE_DOCTYPE_PUBLIC_IDENTIFIER_STATE;
    } else {
      state = State::DOCTYPE_PUBLIC_IDENTIFIER_QUOTED_STATE;
    }
    return;
  }

  if (str[0] == '>') {
    // This is an abrupt-doctype-system-identifier parse error.
    // Set the DOCTYPE token's force-quirks flag to on. Switch to the data state. Emit that DOCTYPE token.
    std::get<0>(functions)(std::make_shared<HTMLTagStartState>(HTMLTagStartState::State::STATE_DATA, HTMLTagType::DATA));
    return;
  }

  // Append the current input character to the current DOCTYPE token's system identifier.

  if (state == State::BEFORE_DOCTYPE_PUBLIC_IDENTIFIER_STATE) {
    //This is a missing-quote-before-doctype-public-identifier parse error. Set the DOCTYPE token's force-quirks flag to on. Reconsume in the bogus DOCTYPE state.
    return;
  }

}
