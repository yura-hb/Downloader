#include "Response.hpp"

const std::string Response::separator = "\r\n";
const std::string Response::doubleSeparator = "\r\n\r\n";

Data<> Response::loadHeader(const Header::_Header& type) const {
  auto result = std::find_if(headers.begin(), headers.end(), [type](const Header& header) {
    return header.header == type;
  });

  return result == headers.end() ? Data<>() : result -> parameters;
}

void Response::setStatus() {
  Data<> firstLine = response.subsequence(response.begin(), response.find(separator, response.begin()));
  status = ResponseStatus(firstLine.stringRepresentation());
}

void Response::setHeaders() {
  Data<> headers = response.subsequence(response.begin(), response.find(doubleSeparator, response.begin()));

  headers.forEachInterval(separator, [this](const Data<>& data)  {
    try {
      Header header(data);
      this -> headers.push_back(header);
    } catch (const std::exception& exc) {}
  });
}
