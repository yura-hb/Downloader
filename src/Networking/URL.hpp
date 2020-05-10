#ifndef __URL_H__
#define __URL_H__

#include<iostream>
#include<regex>
#include<string>
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
  std::string port = "";
  std::string query = "";
  std::string parameters = "";

  URL() = default;
  URL(const std::string &url);
  ~URL() = default;
  /**
   * Discussion:
   *   - Convert url from components to string format
   */
  std::string requestUrl() const;
  /**
   * Discussion:
   *   - Validaties if the URL is valid
   */
  bool isValid() const;
  private:
    /**
     * REGEX description:
     *
     *  1. First group - optional protocol http, ftp, https
     *  2. Server domain group
     *  3. Port
     *  4. Query
     *  5. Parameters
     *
     */
    static const std::string regexString;
    /**
     * Discussion:
     *   - Consumes the string and sets all URL parameters
     */
    void parse(const std::string &str);
};


#endif
