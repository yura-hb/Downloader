#ifndef __HTTP_CLIENT_N__
#define __HTTP_CLIENT_N__

#include "Socket.hpp"
#include "Receiver.hpp"
#include "URL.hpp"
#include "Request.hpp"
#include "../HTTPParser.hpp"
#include "ResponseStatus.hpp"

class HTTPClient {
  public:
    // Default web port is 80, but connection using other ports is not prohibited
    HTTPClient(std::string port = "80") : port(port) {}

    bool loadPage(const std::string &url, std::string &result);
  private:
    std::string port = "80";
    /**
     * Performs the whole pipeline of the HTTP request:
     *  1. Creates socket and connects to it
     *  2. Upload message
     *  3. Fetch message
     *  4. Disconnects from the server
     */
    bool performRequest(Request request, std::string &result);
    /**
     * Parsers headers of the response
     */
    bool proceedResponse(const std::string &headers, const std::string &message);
    /**
     * Converts string url to the URL object
     */
    URL convertLink(const std::string& url) const;
    /**
     * Make basic request
     */
    Request makeRequest(const URL& url) const;
};


#endif
