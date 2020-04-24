#include "ResponseStatus.hpp"

ResponseStatus::ResponseStatus(const std::string& statusLine) {
  std::istringstream text(statusLine);
  std::vector<std::string> splitted { std::istream_iterator<std::string>(text),
                                      std::istream_iterator<std::string>() };

  intCode = std::stoi(splitted.at(1));
  code = (_ResponseStatusCode)intCode;
}

bool ResponseStatus::isFailed() const {
  return intCode >= 300;
}

bool ResponseStatus::isSucceessful() const {
  return intCode >= 200 && intCode < 300;
}

bool ResponseStatus::isRedirection() const {
  return intCode >= 300 && intCode < 400;
}
