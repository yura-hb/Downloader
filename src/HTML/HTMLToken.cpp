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

std::string HTMLDocktypeToken::description() const {
  std::ostringstream out;
  out << "HTMLDocktypeToken" << std::endl;
  out << "Name: " << name << std::endl;
  out << "Public: " << publicId << std::endl;
  out << "Private: " << privateId << std::endl;
  out << "Force quirk: " << forceQuirkFlag << std::endl;
  return out.str();
}

std::string HTMLStartTagToken::description() const {
  std::ostringstream out;
  out << "HTMLStartTagToken" << std::endl;
  out << "Name: " << tagName << std::endl;
  for (const auto& attribute: attributes)
    out << "Attribute: key " << attribute.first << " value: " << attribute.second << std::endl;
  out << "Is closed: " << isSelfClosed << std::endl;
  return out.str();
}

std::string HTMLEndTagToken::description() const {
  std::ostringstream out;
  out << "HTMLEndTagToken" << std::endl;
  out << "Name: " << tagName << std::endl;
  // for (const auto& attribute: attributes)
  //  out << "Attribute: key " << attribute.first << " value: " << attribute.second << std::endl;
  out << "Is closed: " << isSelfClosed << std::endl;
  return out.str();
}

std::string HTMLCommentToken::description() const {
  std::ostringstream out;
  out << "HTMLCommentToken" << std::endl;
  out << "Data: " << data << std::endl;
  return out.str();
}

std::string HTMLCharacterToken::description() const {
   std::ostringstream out;
  out << "HTMLCharacterToken" << std::endl;
  out << "Char sequence: " << data << std::endl;
  return out.str();
}
