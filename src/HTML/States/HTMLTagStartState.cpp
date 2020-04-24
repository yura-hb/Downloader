#include "HTMLTagStartState.hpp"


void HTMLTagStartState::next(const std::string& str, const NextStateFunctions& functions) {
  switch (state) {
  case (HTMLTagStartState::State::STATE_DATA): dataStateAction(str, functions); break;
  case (HTMLTagStartState::State::LESS_THAN_SIGN): lessThanSignStateAction(str, functions); break;
  case (HTMLTagStartState::State::TAG_OPEN_STATE): tagOpenStateAction(str, functions); break;
  case (HTMLTagStartState::State::END_TAG_OPEN_STATE): endTagOpenStateAction(str, functions); break;
  }
}
// DONE
void HTMLTagStartState::dataStateAction(const std::string& str, const NextStateFunctions& functions) {
  if (str == "&" && (type == HTMLTagType::DATA || type == HTMLTagType::RC_DATA)) {

  } else if (str == "<" && type != HTMLTagType::PLAIN_TEXT) {
    state = type == HTMLTagType::DATA ? HTMLTagStartState::State::TAG_OPEN_STATE : HTMLTagStartState::State::LESS_THAN_SIGN;
  } else {
    functions().emit(std::make_unique<HTMLCharacterToken>(str));
  }
}
// DONE
void HTMLTagStartState::lessThanSignStateAction(const std::string& str, const NextStateFunctions& functions) {
  if (str == "/") {
    // Set the temporary buffer to the empty string.
    state = HTMLTagStartState::State::END_TAG_OPEN_STATE;
    return;
  }
  if (str == "!" && type == HTMLTagType::SCRIPT_DATA) {
    // Emit a U+003C LESS-THAN SIGN character token and a U+0021 EXCLAMATION MARK character token.
    return;
  }
  reset("<", functions);
}

// DONE
void HTMLTagStartState::tagOpenStateAction(const std::string& str, const NextStateFunctions& functions) {
  if (type != HTMLTagType::DATA) { return; }

  if (str[0] == '!') {
    //Switch to the markup declaration open state.
    return;
  }

  if (str[0] == '/') {
    state = HTMLTagStartState::State::END_TAG_OPEN_STATE;
    return;
  }

  if (std::isalpha(str[0])) {
    functions().setState(std::make_shared<HTMLTagNameState>(type));
    functions().setToken(std::make_shared<HTMLStartTagToken>());
    functions().setReconsumeState();
    return;
  }

  if (str[0] == '!') {
    // This is an unexpected-question-mark-instead-of-tag-name parse error.
    // Create a comment token whose data is the empty string.
    // Reconsume in the bogus comment state.
    return;
  }

  reset("<", functions);
}

// DONE
void HTMLTagStartState::endTagOpenStateAction(const std::string& str, const NextStateFunctions& functions) {

  if (std::isalpha(str[0])) {
    functions().setState(std::make_shared<HTMLTagNameState>(type));
    functions().setToken(std::make_shared<HTMLEndTagToken>());
    functions().setReconsumeState();
    return;
  }

  if (type == HTMLTagType::DATA) {
    if (str == ">") {
      state = HTMLTagStartState::State::STATE_DATA;
      return;
    }

    if (true) {
      // This is an invalid-first-character-of-tag-name parse error.
      // Create a comment token whose data is the empty string. Reconsume in the bogus comment state.
      return;
    }
  }

  reset("</", functions);
}

// Helpers
void HTMLTagStartState::reset(const std::string& str, const NextStateFunctions& functions) {
  state =  HTMLTagStartState::State::STATE_DATA;
  functions().setToken(std::make_shared<HTMLCharacterToken>("<"));
  functions().setReconsumeState();
}
