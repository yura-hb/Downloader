#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__

#include <iostream>
#include <string>

struct HTTPRequest {
  /**
   * HTTP Method:
   *    - GET - loads data from the specific url
   *    - HEAD - loads info about the specific url
   *    - POST - posts data to the server
   *    - PUT - upload data to the server
   *    - DELETE - delete data from the server
   *    - TRACE - send copy of the request to the client
   *    - OPTIONS - asks server about which methods support
   *    - CONNECT - connect with the object throughout specific port. Commonly used during SSL connection
   */
  enum HTTPRequestType {
    GET,
    HEAD,
    POST,
    PUT,
    DELETE,
    TRACE,
    OPTIONS,
    CONNECT
  };
  /**
   * Supports only v1_1, v2_0 need to be added later
   */
  enum HTTPRequestVersion {
    v1_1,
    v2_0
  };

  const std::string url;
  const HTTPRequestType type;
  const HTTPRequestVersion version;

  HTTPRequest(const std::string &url, const HTTPRequestType &type, const HTTPRequestVersion &version): url(url), type(type), version(version) {}
  /**
   * Creates request in the next format:
   *    TYPE URL HTTP/$(HTTP_REQUEST_VERSION) \r\n
   * !!! Ends the request message with CRLF for more info, please check RFC2068
   */
  std::string createRequest();

  private:
    std::string convertTypeToString();
    std::string convertVersionToString();
};

#endif
