#ifndef __REQUEST_TYPE_H__
#define __REQUEST_TYPE_H__

#include <iostream>
#include <string>
#include <vector>
#include "../Templates/StringConvertible.hpp"

struct RequestMethod: public StringConvertible {
  public:
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
    enum class _RequestMethod {
      GET,
      HEAD,
      POST,
      PUT,
      DELETE,
      TRACE,
      OPTIONS,
      CONNECT
    };

    RequestMethod(const _RequestMethod method): method(method) {}

    std::string description() const override;
  private:
    static const std::vector<std::string> store;
    _RequestMethod method;
};

#endif
