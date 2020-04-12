#include "HTMLToken.hpp"

void HTMLDocktypeToken::setFlagEnabled() { forceQuirkFlag = true; }
HTMLToken::HTMLTokenType HTMLDocktypeToken::getType() const { return HTMLToken::HTMLTokenType::DOCTYPE; }

void HTMLStartTagToken::setFlagEnabled() { isSelfClosed = true; }
HTMLToken::HTMLTokenType HTMLStartTagToken::getType() const { return HTMLToken::HTMLTokenType::START_TAG; }

void HTMLEndTagToken::setFlagEnabled() { isSelfClosed = true; }
HTMLToken::HTMLTokenType HTMLEndTagToken::getType() const { return HTMLToken::HTMLTokenType::END_TAG; }

void HTMLCommentToken::setFlagEnabled() {}
HTMLToken::HTMLTokenType HTMLCommentToken::getType() const { return HTMLToken::HTMLTokenType::COMMENT; }

void HTMLCharacterToken::setFlagEnabled() {}
HTMLToken::HTMLTokenType HTMLCharacterToken::getType() const { return HTMLToken::HTMLTokenType::CHARACTER; }

void HTMLEOFToken::setFlagEnabled() {}
HTMLToken::HTMLTokenType HTMLEOFToken::getType() const { return HTMLToken::HTMLTokenType::END_OF_FILE; }
