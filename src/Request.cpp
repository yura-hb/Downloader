#include "Request.hpp"

std::string Request::createRequest() {
  std::string req  = method.convert() + spaceSeparator + url.query + spaceSeparator  + version.convert() + newLineSeparator;

  for (const auto& header: headers)
    req += header.convert() + newLineSeparator;

  req += newLineSeparator;

  return req;
}

