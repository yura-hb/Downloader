#ifndef __HEADER_H__
#define __HEADER_H__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "../Templates/StringConvertible.hpp"

struct Header: public StringConvertible {
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
      PRAGMA
    };
    // - Type of the header
    _Header header;
    // - Content string
    std::string parameters;
    /**
     * Parses string and converts it in the header type and parameters
     */
    Header(const std::string& header);
    /**
     * Base construct, which is ready to be parsed to string
     */
    Header(const _Header& header, const std::string& parameters) noexcept: header(header), parameters(parameters) {}

    std::string description() const override;

    friend std::ostream& operator<< (std::ostream& output, const Header& header);
  private:
    static const std::vector<std::string> store;
};

#endif
