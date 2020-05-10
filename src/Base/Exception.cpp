#include "Exception.hpp"

const char * Exception::what() const noexcept {
  return object.c_str();
}
