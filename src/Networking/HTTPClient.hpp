#ifndef __HTTP_CLIENT_N__
#define __HTTP_CLIENT_N__

#include <algorithm>
#include "Socket.hpp"
#include "Receiver.hpp"
#include "URL.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "ResponseStatus.hpp"
#include "../Base/Data.hpp"

class HTTPClient {
  public:
    // Default web port is 80, but connection using other ports is not prohibited
    HTTPClient(std::string port = "80") : port(port) {}
    bool loadPage(const std::string &url, Response &response) const;
    bool loadPage(const URL& url, Response& response) const;
  private:
    std::string port = "80";
    /**
     *  Discussion:
     *    Performs the whole pipeline of the HTTP request:
     *     1. Creates socket and connects to it
     *     2. Upload message
     *     3. Fetch message
     *     4. Disconnects from the server
     *
     *  Input:
     *    - @param[in] request
     *    - @param[in] result - reference to the data.
     *
     *  Output:
     *    - @param[out] - true, in case, if no error occurred.
     */
    bool performRequest(Request request, Data<> &result) const;
    /**
     *  Discussion:
     *    Converts string url to the URL object.
     *
     *  Input:
     *    - @param[in] url - string representation of the url.
     *
     *  Output:
     *    - @param[out] - url object
     */
    URL convertLink(const std::string& url) const;
    /**
     *  Input:
     *    - @param[in] url - url object.
     *  Output:
     *    - @param[out] - request object.
     */
    Request makeRequest(const URL& url) const;
};


#endif
