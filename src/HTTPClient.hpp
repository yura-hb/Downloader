#ifndef __HTTP_CLIENT_N__
#define __HTTP_CLIENT_N__

#include "Socket.hpp"
#include "Receiver.hpp"
#include "URL.hpp"
#include "HTTPRequest.hpp"

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
    bool performRequest(HTTPRequest request, std::string &result);
};


#endif
