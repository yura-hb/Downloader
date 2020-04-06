#ifndef __HEADER_PARSER_H__
#define __HEADER_PARSER_H__

#include "iostream"
#include "string"
#include "vector"
#include "map"
#include "sstream"
#include "Header.hpp"

class HeaderParser {
  public:
    static const std::vector<Header> parse(const std::string headers);
};
#endif
