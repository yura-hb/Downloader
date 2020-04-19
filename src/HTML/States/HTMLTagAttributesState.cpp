#include "HTMLTagAttributesState.hpp"

void HTMLTagAttributesState::next(const std::string& str, const NextStateFunctions& functions) {
  switch (state) {
  case HTMLTagAttributesState::State::BEFORE_ATTRIBUTE_NAME:
    beforeAttributeNameAction(str, functions);
    break;
  case HTMLTagAttributesState::State::ATTRIBUTE_NAME_STATE:
    attributeNameAction(str, functions);
    break;
  case HTMLTagAttributesState::State::AFTER_ATTRIBUTE_NAME_STATE:
    afterAttributeNameAction(str, functions);
    break;
  case HTMLTagAttributesState::State::BEFORE_ATTRIBUTE_VALUE_STATE:
    beforeAttributeValueAction(str, functions);
    break;
  case HTMLTagAttributesState::State::BEFORE_ATTRIBUTE_VALUE_QUOTED_STATE:
    beforeAttributeQuotedState(str, functions);
    break;
  case HTMLTagAttributesState::State::ATTRIBUTE_VALUE_UNQUOTED_STATE:
    attributeValueUnquotedState(str, functions);
    break;
  case HTMLTagAttributesState::State::AFTER_ATTRIBUTE_VALUE_QUOTED_STATE:
    afterAttributeValueQuotedState(str, functions);
    break;
  }
}

void HTMLTagAttributesState::beforeAttributeNameAction(const std::string& str, const NextStateFunctions& functions) {
  if (std::find(whitespaceCharacters.begin(), whitespaceCharacters.end(), str[0]) != whitespaceCharacters.end())
      return;

  if (str[0] == '/' || str[0] == '>') {
    state = HTMLTagAttributesState::State::AFTER_ATTRIBUTE_NAME_STATE;
    std::get<2>(functions)(true);
    return;
  }

  if (str[0] == '=') {
    //  Start a new attribute in the current tag token.
    // Set that attribute's name to the current input character, and its value to the empty string. Switch to the attribute name state.
    //   Anything else
    state = HTMLTagAttributesState::State::ATTRIBUTE_NAME_STATE;
    return;
  }
  // Start a new attribute in the current tag token.
  // Set that attribute name and value to the empty string.
  // Reconsume in the attribute name state.
  state = HTMLTagAttributesState::State::ATTRIBUTE_NAME_STATE;
  std::get<2>(functions)(true);
}

void HTMLTagAttributesState::attributeNameAction(const std::string& str, const NextStateFunctions& functions) {
  if (std::find(whitespaceCharacters.begin(), whitespaceCharacters.end(), str[0]) != whitespaceCharacters.end() ||
      str[0] == '/' || str[0] == '>') {
    state = HTMLTagAttributesState::State::AFTER_ATTRIBUTE_NAME_STATE;
    std::get<2>(functions)(true);
    return;
  }

   if (str[0] == '=') {
    //  Start a new attribute in the current tag token.
    // Set that attribute's name to the current input character, and its value to the empty string. Switch to the attribute name state.
    //   Anything else
    state = HTMLTagAttributesState::State::BEFORE_ATTRIBUTE_VALUE_STATE;
    return;
  }

   if (std::isalpha(str[0])) {
    // Append the lowercase version of the current input character (add 0x0020 to the character's code point) to the current attribute's name. U+0000 NULL
    return;
  }

   if (str[0] == '\0') {
    // This is an unexpected-null-character parse error. Append a U+FFFD REPLACEMENT CHARACTER character to the current attribute's name.
    return;
  }

   // Append the current input character to the current attribute's name.
  //
  // When the user agent leaves the attribute name state (and before emitting the tag token, if appropriate),
  // the complete attribute's name must be compared to the other attributes on the same token; if there is already
  // an attribute on the token with the exact same name, then this is a duplicate-attribute parse error and the new attribute
  // must be removed from the token.
}

void HTMLTagAttributesState::afterAttributeNameAction(const std::string& str, const NextStateFunctions& functions) {
  if (std::find(whitespaceCharacters.begin(), whitespaceCharacters.end(), str[0]) != whitespaceCharacters.end())
      return;

  if (str[0] == '/') {
    // Switch to the self-closing start tag state.
    return;
  }

   if (str[0] == '=') {
    state = HTMLTagAttributesState::State::BEFORE_ATTRIBUTE_VALUE_STATE;
    return;
  }

   if (str[0] == '>') {
    // Switch to the data state. Emit the current tag token.
    std::get<0>(functions)(std::make_shared<HTMLTagStartState>(HTMLTagStartState(HTMLTagStartState::State::STATE_DATA, HTMLTagType::DATA)));
    return;
  }

   // Start a new attribute in the current tag token.
  // Set that attribute name and value to the empty string.
  // Reconsume in the attribute name state.
  state = HTMLTagAttributesState::State::ATTRIBUTE_NAME_STATE;
  std::get<2>(functions)(true);
}

void HTMLTagAttributesState::beforeAttributeValueAction(const std::string& str, const NextStateFunctions& functions) {
  if (std::find(whitespaceCharacters.begin(), whitespaceCharacters.end(), str[0]) != whitespaceCharacters.end())
      return;

  if (str[0] == '>') {
    // Switch to the data state. Emit the current tag token.
    std::get<0>(functions)(std::make_shared<HTMLTagStartState>(HTMLTagStartState(HTMLTagStartState::State::STATE_DATA, HTMLTagType::DATA)));
    return;
  }

  if (str[0] == '\"' || str[0] == '\'') {
    state = HTMLTagAttributesState::State::BEFORE_ATTRIBUTE_VALUE_QUOTED_STATE;
    return;
  }

  state =  HTMLTagAttributesState::State::ATTRIBUTE_VALUE_UNQUOTED_STATE;
  std::get<2>(functions)(true);
}

void HTMLTagAttributesState::beforeAttributeQuotedState(const std::string& str, const NextStateFunctions& functions) {
  if (str[0] == '\"' || str[0] == '\'') {
     state = HTMLTagAttributesState::State::AFTER_ATTRIBUTE_VALUE_QUOTED_STATE;
     return;
   }
   if (str[0] == '&') {
     // Set the return state to the attribute value (single-quoted) state. Switch to the character reference state.
     return;
   }
   if (str[0] == '\0') {
     // This is an unexpected-null-character parse error. Append a U+FFFD REPLACEMENT CHARACTER character to the current attribute's name.
     return;
   }
   // Append the current input character to the current attribute's value.
}

void HTMLTagAttributesState::attributeValueUnquotedState(const std::string& str, const NextStateFunctions& functions) {
  if (std::find(whitespaceCharacters.begin(), whitespaceCharacters.end(), str[0]) != whitespaceCharacters.end()) {
    state = HTMLTagAttributesState::State::BEFORE_ATTRIBUTE_VALUE_STATE;
    return;
  }

 if (str[0] == '&') {
    // Set the return state to the attribute value (unquoted) state. Switch to the character reference state.
    return;
  }

 if (str[0] == '>') {
    // Switch to the data state. Emit the current tag token.
    std::get<0>(functions)(std::make_shared<HTMLTagStartState>(HTMLTagStartState(HTMLTagStartState::State::STATE_DATA, HTMLTagType::DATA)));
    return;
  }

 if (str[0] == '\0') {
    // This is an unexpected-null-character parse error. Append a U+FFFD REPLACEMENT CHARACTER character to the current attribute's name.
    return;
  }
  // Append the current input character to the current attribute's value.
}

void HTMLTagAttributesState::afterAttributeValueQuotedState(const std::string& str, const NextStateFunctions& functions) {
  if (std::find(whitespaceCharacters.begin(), whitespaceCharacters.end(), str[0]) != whitespaceCharacters.end()) {
    state = HTMLTagAttributesState::State::BEFORE_ATTRIBUTE_VALUE_STATE;
    return;
  }
  if (str[0] == '/') {
    // Switch to the self-closing start tag state.
    return;
  }
  if (str[0] == '>') {
    // Switch to the data state. Emit the current tag token.
    std::get<0>(functions)(std::make_shared<HTMLTagStartState>(HTMLTagStartState::State::STATE_DATA, HTMLTagType::DATA));
    return;
  }
  if (str[0] == '\0') {
    // This is an unexpected-null-character parse error. Append a U+FFFD REPLACEMENT CHARACTER character to the current attribute's name.
    return;
  }
   // This is a missing-whitespace-between-attributes parse error. Reconsume in the before attribute name state.
   state = HTMLTagAttributesState::State::BEFORE_ATTRIBUTE_VALUE_STATE;
   std::get<2>(functions)(true);
}
