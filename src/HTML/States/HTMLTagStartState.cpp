#include "HTMLTagStartState.hpp"

void HTMLTagStartState::next(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions) {
  std::cout << str << ((int)state) << " ";
  switch (state) {
  case (HTMLTagStartState::State::STATE_DATA): dataStateAction(str, functions); break;
  case (HTMLTagStartState::State::LESS_THAN_SIGN): lessThanSignStateAction(str, functions); break;
  case (HTMLTagStartState::State::TAG_OPEN_STATE): tagOpenStateAction(str, functions); break;
  case (HTMLTagStartState::State::END_TAG_OPEN_STATE): endTagOpenStateAction(str, functions); break;
  case (HTMLTagStartState::State::MARKUP_DECLARATION): markupDeclarationStateAction(str, functions); break;
  }
}

void HTMLTagStartState::dataStateAction(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions) {
  if (str == "&" && (type == HTMLTagType::DATA || type == HTMLTagType::RC_DATA)) {

  } else if (str == "<" && type != HTMLTagType::PLAIN_TEXT) {
    state = type == HTMLTagType::DATA ? HTMLTagStartState::State::TAG_OPEN_STATE : HTMLTagStartState::State::LESS_THAN_SIGN;
    return;
  }
  functions().emit(std::make_unique<HTMLCharacterToken>(str));
}

void HTMLTagStartState::lessThanSignStateAction(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions) {
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
void HTMLTagStartState::tagOpenStateAction(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions) {
  if (type != HTMLTagType::DATA) { return; }

  if (str == "!") {
    //Switch to the markup declaration open state.
    state = State::MARKUP_DECLARATION;
    return;
  }

  if (str == "/") {
    state = HTMLTagStartState::State::END_TAG_OPEN_STATE;
    return;
  }

  if (std::isalpha(str[0])) {
   // functions().setState(std::make_shared<HTMLTagNameState>(type));
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
void HTMLTagStartState::endTagOpenStateAction(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions) {

  if (std::isalpha(str[0])) {
   // functions().setState(std::make_shared<HTMLTagNameState>(type));
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

void HTMLTagStartState::markupDeclarationStateAction(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions) {
  if (functions().substring(2) == "--") {
    // Create a comment token whose data is the empty string, and switch to the comment start state
    return;
  } else if (functions().substring(7) == "[CDATA[") {
    // Consume those characters. If there is an adjusted current node and it is not an element in the HTML namespace,
    // then switch to the CDATA section state. Otherwise, this is a cdata-in-html-content parse error. Create a comment token whose data is the "[CDATA[" string. Switch to the bogus comment state.
    //
    return;
  }

  auto substr = functions().substring(7);

  std::for_each(substr.begin(), substr.end(), [](char & c) {
    c = std::tolower(c);
  });

  if (substr == "doctype") {
    functions().setState(std::make_shared<HTMLDoctypeState>(HTMLDoctypeState::State::DOCTYPE_STATE));
    functions().setToken(std::make_shared<HTMLDocktypeToken>());
    return;
  }
  //  Create a comment token whose data is the empty string.
  //  Switch to the bogus comment state (don't consume anything in the current state).


  return;

}

// Helpers
void HTMLTagStartState::reset(const std::string& str, const std::function<HTMLTokenizerContext&(void)> functions) {
  state =  HTMLTagStartState::State::STATE_DATA;
  functions().setToken(std::make_shared<HTMLCharacterToken>("<"));
  functions().setReconsumeState();
}
