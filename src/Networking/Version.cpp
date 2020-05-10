#include "Version.hpp"

const std::vector<std::string> Version::store = { "HTTP/1.1", "HTTP/2.0" };

std::string Version::description() const {
  return store[static_cast<int>(version)];
}
