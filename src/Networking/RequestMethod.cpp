#include "RequestMethod.hpp"

const std::vector<std::string> RequestMethod::store = { "GET", "HEAD", "POST", "PUT", "DELETE", "TRACE", "OPTIONS", "CONNECT" };

std::string RequestMethod::description() const {
  return store[static_cast<int>(method)];
}
