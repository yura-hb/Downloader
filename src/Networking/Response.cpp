#include "Response.hpp"

const std::string Response::separator = "\r\n\r\n";
const std::string Response::doubleSeparator = "\r\n\r\n";
const std::string Response::headerParametersSeparator = ", ";
const std::string Response::textContentTypePrefix = "text/";

std::string Response::loadHeader(const Header::_Header& type) const {
  auto result = std::find_if(headers.begin(), headers.end(), [type](const Header& header) {
    return header.header == type;
  });

  return result == headers.end() ? "" : result -> parameters;
}

Data<> Response::loadBody() const {
  Data<> body = response.subsequence(response.find(doubleSeparator, response.begin()), response.end());

  //processTransferEncoding(body);

  std::string contentType = loadHeader(Header::_Header::CONTENT_TYPE);

  if (std::mismatch(textContentTypePrefix.begin(),
                    textContentTypePrefix.end(),
                    contentType.begin(),
                    contentType.end()).first == textContentTypePrefix.end()) {
    // Convert from CRLF to LF to unix separator(LF)
    #ifdef unix
      size_t pos = 0;
      while ((pos = body.find(pos, "\r\n")) != std::string::npos)
        body.erase(pos);
    #endif
  }

  return response;
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

const std::string Response::getHeader(const std::string& response) const {
  auto index = response.find(separator);
  return std::string(response.begin(), response.begin() + index);
}

void Response::processTransferEncoding(std::string& body) const {
  std::string transferEncoding = "chuncked, test, test, test"; //loadHeader(Header::_Header::TRANSFER_ENCODING);

  if (transferEncoding == "")
    return;

  std::vector<std::string> components;

  auto prev = transferEncoding.begin();
  auto next = transferEncoding.begin();

  std::cout << headerParametersSeparator << std::endl;

  while ((next = std::search(next,
                             transferEncoding.end(),
                             headerParametersSeparator.begin(),
                             headerParametersSeparator.end())) != transferEncoding.end()) {
    auto offset = headerParametersSeparator.size();
    components.push_back(std::string(prev, next + offset));
    prev = next + offset;
    next += offset + 1;
  }
  components.push_back(std::string(prev, next));

  for (const auto& component : components) {
    std::cout << component << std::endl;
  }
}
