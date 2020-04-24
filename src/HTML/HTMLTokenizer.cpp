#include "HTMLTokenizer.hpp"

void HTMLTokenizer::parse(const std::string& str) {
  // Initial state is the dataState
  context.setState(std::make_shared<HTMLTagStartState>(HTMLTagStartState::State::STATE_DATA, HTMLTagType::DATA));
  //context.tokenizer = this -> shared_from_this();

  parsingIndex = 0;
  parsingDataReference = std::shared_ptr<const std::string>(&str);

  auto index = str.begin();

  std::cout << "Parsing: " << str << std::endl;

  while (index != str.end()) {
    /**
     * Provide the reference of the context, to update context.
     * !!! Cuz of it is the combination of the reference and pvalue, storing of the reference
     *     will create dangling problem
     */
    context.getState() -> next(std::string(1, *index), [this]() -> HTMLTokenizerContext& {
      return this -> context;
    });

    if (context.getReconsumeState()) {
      context.prepareForNextState();
      continue;
    }

    index++;
    parsingIndex++;
    context.prepareForNextState();
  }

  //context.tokenizer = nullptr;
  parsingIndex = 0;
  parsingDataReference = nullptr;
}

std::string HTMLTokenizer::substring(size_t length) {
  if (parsingDataReference == nullptr)
    return "";

  if (parsingDataReference -> begin() + parsingIndex + length > parsingDataReference -> end())
    return std::string(parsingDataReference -> begin() + parsingIndex, parsingDataReference -> end());

  return std::string(parsingDataReference -> begin() + parsingIndex,
                     parsingDataReference -> begin() + parsingIndex + length);
}
