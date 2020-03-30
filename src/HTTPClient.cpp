#include "HTTPClient.hpp"

bool HTTPClient::loadPage(const std::string &url, const std::string hostname, std::string &result) {
  HTTPRequest request(url, HTTPRequest::HTTPRequestType::GET, HTTPRequest::HTTPRequestVersion::v1_1);
  std::cout << request.createRequest() << std::endl;
  return performRequest(request, hostname, result);
}

bool HTTPClient::performRequest(HTTPRequest request, const std::string hostname, std::string &result) {
  Socket sock(hostname.c_str(), port.c_str());

  uint32_t sentBytes = 0;
  const std::string message = request.createRequest();

  if (!sock.connect() || !sock.send(message, sentBytes))
    return false;

  Receiver receiver;

  receiver.receivePage(result, sock);

  sock.disconnect();

  return true;
}

