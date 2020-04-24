#include "HTMLTokenizer.hpp"

void HTMLTokenizer::parse(const std::string& str) {
  // Initial state is the dataState
  context.setState(std::make_shared<HTMLTagStartState>(HTMLTagStartState::State::STATE_DATA, HTMLTagType::DATA));

  auto index = str.begin();

  while (index != str.end()) {
    // TODO: - Describe, why give reference
    context.getState() -> next(std::to_string(*index), [this]() -> HTMLTokenizerContext& {
      return this -> context;
    });

    if (context.getReconsumeState()) {
      context.prepareForNextState();
      continue;
    }

    index++;
    context.prepareForNextState();
  }
}
