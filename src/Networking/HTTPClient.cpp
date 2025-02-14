#include "HTTPClient.hpp"

bool HTTPClient::loadPage(const URL& url, Response& response) const {
  Request request = makeRequest(url);

  Logger::logRequest(request);

  Data<> data("");

  if (!performRequest(request, data))
    return false;

  try {
    response = { data, url };
  } catch (const Exception &exc) {
    Logger::logError(exc);
    return false;
  }

  return true;
}

bool HTTPClient::loadPage(const std::string &url,
                          Response& response) const {
  URL link = convertLink(url);
  return loadPage(link, response);
}

bool HTTPClient::performRequest(Request request, Data<> &result) const {
  Socket sock(request.url.domain.c_str(), port.c_str());

  uint32_t sentBytes = 0;
  const std::string message = request.createRequest();

  if (!sock.connect() || !sock.send(message, sentBytes))
    return false;

  Receiver receiver;
  receiver.receivePage(result, sock);
  sock.disconnect();
  return true;
}

/**
 * Helpers
 */
URL HTTPClient::convertLink(const std::string& url) const {
  URL link(url);

  if (!link.isValid() || link.protocol != URL::Protocol::http)
    Logger::logError(Exception("HTTPClient: Link is incorrect or protocol is not SUPPORTED"));

  return link;
}

Request HTTPClient::makeRequest(const URL& url) const {
  RequestMethod method(RequestMethod::_RequestMethod::GET);
  Version version(Version::_Version::v1_1);
  std::vector<Header> headers = {
    Header(Header::_Header::HOST, url.domain),
    Header(Header::_Header::ACCEPT_ENCODING, "identity, chunked"),
    Header(Header::_Header::CONNECTION, "Close")
  };

  return Request(url, method, version, headers);
}
