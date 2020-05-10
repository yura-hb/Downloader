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
     *  Discussion:
     *    Parses string and converts it in the header type and parameters.
     *    The format of the header is the next, Header: params\r\n.
     *
     *  Input:
     *    - @param[in] header - data representation of the header.
     *
     *  Throws:
     *    * In case, if header type is not found, throws Exception.
     *    * In case, if header is in the incorrect format, throws Exception.
     *
     */
    Header(const Data<>& header);
    /**
     * Discussion:
     *   Base construct, which is ready to be parsed to string
     *
     * Input:
     *   - @param[in] header - header type
     *   - @param[in] parameters - parameters of the header
     */
    Header(const _Header& header, const std::string& parameters) noexcept: header(header), parameters(parameters) {}
    ~Header() {}
    /**
     *  Output:
     *   - @param[out] - string representation of the header.
     */
    std::string description() const;
  private:
    static const std::vector<std::string> store;
};

#endif
