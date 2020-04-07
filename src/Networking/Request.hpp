#ifndef __REQUEST_H__
#define __REQUEST_H__

#include <iostream>
#include <string>
#include <vector>

#include "URL.hpp"
#include "RequestMethod.hpp"
#include "Version.hpp"
#include "Header.hpp"

struct Request {
  const URL url;
  const RequestMethod method;
  const Version version;
  const std::vector<Header> headers;

  Request(const URL &url,
      const RequestMethod &method= RequestMethod::_RequestMethod::GET,
      const Version &version = Version::_Version::v1_1,
      const std::vector<Header>& headers = {}): url(url), method(method), version(version), headers(headers) {}
  /**
   * Creates request in the next format:
   *    `METHOD` SPACE `HOST_QUERY` SPACE `VERSION` CRLF
   *    `HEADER: value` CRLF
   *    CRLF
   * !!! Ends the request message with CRLF for more info, please check RFC2068
   */
  std::string createRequest();

  private:
    std::string spaceSeparator = " ";
    std::string newLineSeparator = "\r\n";
};

#endif
