#ifndef __HEADER_H__
#define __HEADER_H__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "../Base/Exception.hpp"
#include "../Base/Data.hpp"

struct Header {
  public:
    // - Nested
    enum class _Header {
      ACCEPT = 0,
      ACCEPT_CHARSET,
      ACCEPT_ENCODING,
      ACCEPT_LANGUAGE,
      ACCEPT_RANGES,
      AGE,
      ALLOW,
      AUTHORIZATION,
      CACHE_CONTROL,
      CONNECTION,
      CONTENT_ENCODING,
      CONTENT_LANGUAGE,
      CONTENT_LENGTH,
      CONTENT_LOCATION,
      CONTENT_TYPE,
      DATE,
      EXCEPT,
      HOST,
      LOCATION,
      PRAGMA,
      TRANSFER_ENCODING
    };
    // - Type of the header
    _Header header;
    // - Content string
    Data<> parameters;
    /**
     * Parses string and converts it in the header type and parameters
     */
    Header(const Data<>& header);
    /**
     * Base construct, which is ready to be parsed to string
     */
    Header(const _Header& header, const std::string& parameters) noexcept: header(header), parameters(parameters) {}
    ~Header() {}

    std::string description() const;

    friend std::ostream& operator<< (std::ostream& output, const Header& header);
  private:
    static const std::vector<std::string> store;
};

#endif
