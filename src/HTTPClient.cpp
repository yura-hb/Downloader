#include "HTTPClient.hpp"

bool HTTPClient::loadPage(const std::string &url, std::string &result) {
  URL link(url);

  if (!link.isValid() || link.protocol != URL::Protocol::http) {
    std::cerr << "HTTPClient: Link is incorrect or protocol is not SUPPORTED" << std::endl;
    return false;
  }

  HTTPRequest request(link, HTTPRequest::HTTPRequestType::GET, HTTPRequest::HTTPRequestVersion::v1_1);

  std::cout << request.createRequest() << std::endl;
  return performRequest(request, result);
}

bool HTTPClient::performRequest(HTTPRequest request, std::string &result) {
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

