#include "Request.hpp"

std::string Request::createRequest() const {
  std::string req  = method.description() + spaceSeparator + url.query + spaceSeparator  + version.description() + newLineSeparator;

  for (const auto& header: headers)
    req += header.description() + newLineSeparator;

  req += newLineSeparator;

  return req;
}

