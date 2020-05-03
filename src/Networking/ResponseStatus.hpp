#ifndef __RESPONSE_STATUS_H_
#define __RESPONSE_STATUS_H_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>

struct ResponseStatus {
  public:
    enum class _ResponseStatusCode {
      CONTINUE = 100,
      SWITCHING_PROTOCOLS = 101,
      // Success codes
      OK = 200,
      CREATED = 201,
      ACCEPTED = 202,
      NON_AUTH_INFO = 203,
      NO_CONTENT = 204,
      RESET_CONTENT = 205,
      PARTIAL_CONTENT = 207,
      // Redirection codes, need to change url
      MULTIPLE_CHOISES = 300,
      MOVED_PERMANENTLY = 301,
      FOUND = 302,
      SEE_OTHER = 303,
      NOT_MODIFIED = 304,
      USE_PROXY = 305,
      TEMPORARY_REDIRECT = 307,
      // Errors
      BAD_REQUEST = 400,
      UNAUTHORIZED = 401,
      PAYMENT_REQUIRED = 402,
      FORBIDDEN = 403,
      NOT_FOUND = 404,
      METHOD_NOT_ALLOWED = 405,
      NOT_ACCEPTABLE = 406,
      PROXY_AUTHENTIFICATION_REQUIRED = 407,
      REQUEST_TIMEOUT = 408,
      CONFLICT = 409,
      GONE = 410,
      LENGTH_REQUIRED = 411,
      PRECONDITION_REQUIRED = 412,
      REQUEST_ENTITY_TOO_LARGE = 413,
      REQUEST_URI_TOO_LONG = 414,
      USUPPORTED_MEDIA_TYPE =  415,
      // Server errors
      INTERNAL_SERVER_ERROR = 500,
      NOT_IMPLEMNTED = 501,
      BAD_GATAWAY = 502,
      SERVICE_UNAVAILABLE = 503,
      GATAWAY_TIMEOUT = 504,
      HTTP_VERSION_NOT_SUPPORTED = 505
    };
    // Variables
    _ResponseStatusCode code = _ResponseStatusCode::BAD_REQUEST;
    int intCode = (int)_ResponseStatusCode::BAD_REQUEST;

    ResponseStatus() = default;
    /**
     * Initialize ResponseStatus using first line of the responce message
     * The format of the responce is the next:
     *  Version of HTTP -space- Status code -space- message
     */
    ResponseStatus(const std::string& statusLine);
    // Helpers
    /**
     * If status is not 2xx returns false
     */
    bool isFailed() const;
    /**
     * !isFailed()
     */
    bool isSucceessful() const;
    /**
     * If status is 3xx
     */
    bool isRedirection() const;
};

#endif
