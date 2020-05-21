#ifndef __URL_H__
#define __URL_H__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "../Base/Data.hpp"
/**
 * Wrapper around URL
 */
struct URL {
    /**
     * Basic internet connection protocols
     *
     * !! default is http
     */
    enum Protocol {
      undefined, http, https, ftp
    };

    Protocol protocol = Protocol::undefined;
    std::string domain = "";
    std::string query = "";
    std::string parameters = "";

    URL() = default;
    URL(const std::string &url);
    ~URL() = default;
    /**
     * @brief
     *   Convert url from components to string format
     */
    std::string requestUrl() const;
    /**
     * @brief
     *   Validaties if the URL is valid
     */
    bool isValid() const;
    /**
     * @brief
     *   Compares two domains, if they are equal. Skips www domain.
     *   Note:
     *    There can be a wide range of public suffixes in the URL.
     *    So the implementation is not final https://publicsuffix.org/list/.
     */
    static bool compareDomains(const std::string& lhs, const std::string& rhs);
  private:
    /**
     * @brief
     *   Consumes the string and sets all URL parameters
     */
    void parse(const std::string &urlString);

    static const std::string httpPrefix;
    static const std::string httpsPrefix;
    static const std::string ftpPrefix;
    static const std::string wwwPrefix;
};


#endif
