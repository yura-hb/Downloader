#include "Response.hpp"

const std::string Response::separator = "\r\n\r\n";
const std::string Response::headerParametersSeparator = ", ";
const std::string Response::textContentTypePrefix = "text/";

std::string Response::loadHeader(const Header::_Header& type) const {
  auto result = std::find_if(headers.begin(), headers.end(), [type](const Header& header) {
    return header.header == type;
  });

  return result == headers.end() ? "" : result -> parameters;
}

std::string Response::loadBody() const {
  std::string body = std::string(response.begin() + response.find(separator) + separator.size(), response.end());

  processTransferEncoding(body);

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
  std::stringstream splitStream(response);
  std::string line = "";

  if (!getline(splitStream, line))
    throw Exception("Incorrect response");

  status = ResponseStatus(line);
}

void Response::setHeaders() {
  std::vector<Header> components  = {};

  std::stringstream splitStream(getHeader(response));
  std::string line = "";

  while (getline(splitStream, line)) {
    try {
      Header header(line);
      components.push_back(header);
    } catch (const std::exception& exc) {
      continue;
    }
  }

  headers = components;
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
