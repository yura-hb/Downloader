#include "HTTPClient.hpp"

bool HTTPClient::loadPage(const std::string &url, std::string &result) {
  URL link = convertLink(url);

  Request request = makeRequest(link);

  std::string data = "";

  if (!performRequest(request, data))
    return false;

  try {
    ResponseStatus status = Parser::parseStatus(data);
    std::cout << status.intCode << std::endl;

    std::vector<Header> headers = Parser::parse(data);

    for (const auto& header: headers) {
      std::cout << header << std::endl;
    }
  } catch (std::exception &exc) {
    std::cerr << exc.what() << std::endl;
  }

  return true;
}

bool HTTPClient::performRequest(Request request, std::string &result) {
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

  if (!link.isValid() || link.protocol != URL::Protocol::http) {
    std::cerr << "HTTPClient: Link is incorrect or protocol is not SUPPORTED" << std::endl;
  }

  return link;
}

Request HTTPClient::makeRequest(const URL& url) const {
  RequestMethod method(RequestMethod::_RequestMethod::GET);
  Version version(Version::_Version::v1_1);
  std::vector<Header> headers = { Header(Header::_Header::HOST, url.domain), Header(Header::_Header::CONNECTION, "Close") };

  return Request(url, method, version, headers);
}
