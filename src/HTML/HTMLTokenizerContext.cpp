#include "HTMLTokenizerContext.hpp"

void HTMLTokenizerContext::setState(std::shared_ptr<HTMLTokenizerState> state) {
  this -> state = state;
}
void HTMLTokenizerContext::setReconsumeState() {
  shouldReconsume = true;
}
void HTMLTokenizerContext::setToken(std::shared_ptr<HTMLToken> token) {
  this -> token = token;
}
void HTMLTokenizerContext::addToBuffer(const std::string& str) {
  buffer += str;
}
void HTMLTokenizerContext::prepareForNextState() {
  shouldReconsume = false;
}
void HTMLTokenizerContext::emit(const std::shared_ptr<HTMLToken> token) {
  std::cout << token -> description() << std::endl;
}
std::string HTMLTokenizerContext::substring(const size_t length) const {
  return "";
 // return tokenizer -> substring(length);
}
std::shared_ptr<HTMLToken>& HTMLTokenizerContext::getCurrentToken() {
  return token;
}
void HTMLTokenizerContext::emitLocalToken() {

}
//  - Getters
std::shared_ptr<HTMLTokenizerState>& HTMLTokenizerContext::getState() {
  return state;
}
std::string HTMLTokenizerContext::getBuffer() {
  return buffer;
}
bool HTMLTokenizerContext::getReconsumeState() const {
  return shouldReconsume;
}

