#ifndef __RESPONSE__
#define __RESPONSE__

#include <iostream>
#include <string>
#include <vector>

#include "URL.hpp"
#include "Header.hpp"
#include "ResponseStatus.hpp"
#include "../Templates/Data.hpp"

struct Response {
  public:
    Response() = default;
    Response(const Data<>& response, const URL& url) : url(url), response(response) {
      setStatus();
      setHeaders();
    }

    URL url;
    ResponseStatus status;
    std::vector<Header> headers;
    Data<> response;
    /**
     *  Input:
     *    - @param[in] type - the type of the header to exctract.
     *
     *  Output:
     *    - @param[out] - header parameter
     */
    Data<> loadHeader(const Header::_Header& type) const;
  private:
    static const std::string separator;
    static const std::string doubleSeparator;

    void setStatus();
    void setHeaders();
};

#endif
