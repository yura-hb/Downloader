#include "HTTPRequest.hpp"

std::string HTTPRequest::createRequest() {
  return convertTypeToString() + " " + url.query + " " + convertVersionToString() + "\r\n" + "Host: " + url.domain + "\r\n\r\n";
}

std::string HTTPRequest::convertTypeToString() {
  switch (type) {
    case HEAD:
      return "HEAD";
    case GET:
      return "GET";
    case POST:
      return "POST";
    case PUT:
      return "PUT";
    case DELETE:
      return "DELETE";
    case TRACE:
      return "OPTIONS";
    case OPTIONS:
      return "OPTIONS";
    case CONNECT:
      return "CONNECT";
  }
}
std::string HTTPRequest::convertVersionToString() {
  switch (version) {
    case v1_1:
      return "HTTP/1.1";
    case v2_0:
      return "HTTP/2.0";
  }
}

