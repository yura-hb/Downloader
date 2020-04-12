#include "HTMLTagNameState.hpp"

void HTMLTagNameState::next(const std::string& str, const NextStateFunctions& functions) {
  if (std::find(whitespaceCharacters.begin(), whitespaceCharacters.end(), str[0]) != whitespaceCharacters.end()) {
    whitespaceCharacterAction(str, functions);
    return;
  }

  if (str[0] == '/') {
    solidusCharacterAction(str, functions);
    return;
  }

  if (str[0] == '>') {
    greaterThanSignAction(str, functions);
    return;
  }

  if (std::isalpha(str[0])) {
    alphaAction(str, functions);
    return;
  }

  if (str == "\0" && type == HTMLTagType::DATA) {
    nullAction(str, functions);
    return;
  }

  if (str[0] == EOF && type == HTMLTagType::DATA) {
    eofAction(str, functions);
    return;
  }

  otherAction(str, functions);
}

void HTMLTagNameState::whitespaceCharacterAction(const std::string& str, const NextStateFunctions& functions) {
  // Switch to the before attribute name state.
}

void HTMLTagNameState::solidusCharacterAction(const std::string& str, const NextStateFunctions& functions) {
  // Switch to the self-closing start tag state.
}

void HTMLTagNameState::greaterThanSignAction(const std::string& str, const NextStateFunctions& functions) {
  // Switch to the data state. Emit the current tag token.
  std::get<0>(functions)(std::make_shared<HTMLTagStartState>(HTMLTagStartState(HTMLTagStartState::State::STATE_DATA,
                                                                               HTMLTagType::DATA)));
}

void HTMLTagNameState::alphaAction(const std::string& str, const NextStateFunctions& functions) {
  // Append the lowercase version of the current input character
  // (add 0x0020 to the character's code point) to the current tag token's tag name.
  char tmp = std::tolower(str[0]);

}

void HTMLTagNameState::nullAction(const std::string& str, const NextStateFunctions& functions) {
  // This is an unexpected-null-character parse error.
  // Append a U+FFFD REPLACEMENT CHARACTER character to the current tag token's tag name.
}

void HTMLTagNameState::eofAction(const std::string& str, const NextStateFunctions& functions) {
  // DATA
  // This is an eof-before-tag-name parse error.
  // Emit a U+003C LESS-THAN SIGN character token, a U+002F SOLIDUS character token and an end-of-file toke
  std::get<1>(functions)(std::make_unique<HTMLEOFToken>(HTMLEOFToken()));
  return;
}

void HTMLTagNameState::otherAction(const std::string& str, const NextStateFunctions& functions) {
  if (type == HTMLTagType::DATA) {
     // Append the current input character to the current tag token's tag name.
     return;
  }
  std::get<0>(functions)(std::make_shared<HTMLTagStartState>(HTMLTagStartState(HTMLTagStartState::State::STATE_DATA, type)));
  std::get<1>(functions)(std::make_unique<HTMLEOFToken>(HTMLCharacterToken("</")));
  std::get<2>(functions)(true);
}
