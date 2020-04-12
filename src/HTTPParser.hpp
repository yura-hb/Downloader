#ifndef __PARSER_H__
#define __PARSER_H__

#include "iostream"
#include "string"
#include "vector"
#include "map"
#include "sstream"
#include "Networking/ResponseStatus.hpp"
#include "Networking/Header.hpp"

class Parser {
  public:
    /**
     * Parsers response message and extracts first line of the response
     *
     * @param[in] response - full response from the server
     */
    static const ResponseStatus parseStatus(const std::string& response);
    /**
     * Parsers headers of messages
     *
     * @param[in] response - full response from the server
     */
    static const std::vector<Header> parse(const std::string& response);

    /**
     * Parsers headers of messages
     *
     * @param[in] response - full response from the server
     */
    //static const HTMLElement parseHtml(const std::string &response);
  private:
    static const std::string getHeader(const std::string &response);

};
#endif
