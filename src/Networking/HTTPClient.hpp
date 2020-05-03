#ifndef __HTTP_CLIENT_N__
#define __HTTP_CLIENT_N__

#include <algorithm>
#include "Socket.hpp"
#include "Receiver.hpp"
#include "URL.hpp"
#include "Request.hpp"
#include "../HTTPParser.hpp"
#include "ResponseStatus.hpp"

struct Response {
  Response() = default;

  ResponseStatus status;
  std::vector<Header> headers;
  std::string body;
};

class HTTPClient {
  public:
    // Default web port is 80, but connection using other ports is not prohibited
    HTTPClient(std::string port = "80") : port(port) {}
    // TODO: - add exception error handling
    bool loadPage(const std::string &url, Response &response) const;
  private:
    std::string port = "80";
    /**
     * Performs the whole pipeline of the HTTP request:
     *  1. Creates socket and connects to it
     *  2. Upload message
     *  3. Fetch message
     *  4. Disconnects from the server
     */
    bool performRequest(Request request, std::string &result) const;
    /**
     * Parsers headers of the response
     */
    bool proceedResponse(const std::string &headers, const std::string &message) const;
    /**
     * Converts string url to the URL object
     */
    URL convertLink(const std::string& url) const;
    /**
     * Make basic request
     */
    Request makeRequest(const URL& url) const;
    /**
     * Help method to normalise newlines
     */
    void preprocessResponse(std::string& str) const;
};


#endif
