#include "Response.hpp"

const std::string Response::separator = "\r\n";
const std::string Response::doubleSeparator = "\r\n\r\n";
const std::string Response::headerParametersSeparator = ", ";
const std::string Response::textContentTypePrefix = "text/";

Data<> Response::loadHeader(const Header::_Header& type) const {
  auto result = std::find_if(headers.begin(), headers.end(), [type](const Header& header) {
    return header.header == type;
  });

  return result == headers.end() ? Data<>() : result -> parameters;
}

Data<> Response::loadBody() const {
  Data<> body = response.subsequence(response.find(doubleSeparator, response.begin()), response.end());

  processTransferEncoding(body);

  Data<> contentType = loadHeader(Header::_Header::CONTENT_TYPE);

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

void Response::processTransferEncoding(Data<>& body) const {
  Data<> transferEncoding = loadHeader(Header::_Header::TRANSFER_ENCODING);

  if (transferEncoding.empty())
    return;

  transferEncoding.forEachInterval(headerParametersSeparator, [body](const Data<>& data) {

  });
}

void Response::mergeChunks(Data<>& body) const {

}
