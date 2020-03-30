#ifndef __HTTP_CLIENT_N__
#define __HTTP_CLIENT_N__

#include "Socket.hpp"
#include "Receiver.hpp"
#include "HTTPRequest.hpp"

class HTTPClient {
  public:
    // Default web port is 80, but connection using other ports is not prohibited
    HTTPClient(std::string port = "80") : port(port) {}

    // TODO: - Remove hostname from this call
    bool loadPage(const std::string &url, const std::string hostname, std::string &result);
  private:
    std::string port = "80";
    /**
     * Performs the whole pipeline of the HTTP request:
     *  1. Creates socket and connects to it
     *  2. Upload message
     *  3. Fetch message
     *  4. Disconnects from the server
     */
    bool performRequest(HTTPRequest request, const std::string hostname, std::string &result);
};


#endif
