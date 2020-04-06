#ifndef __URL_H__
#define __URL_H__

#include<iostream>
#include<regex>
#include<string>

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

  URL(const std::string &url);
  /**
   * Convert url to the standart request format
   */
  std::string requestUrl() const;
  /**
   * Validates string
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
    const std::string regexString = "^(http\\:\\/\\/|https\\:\\/\\/|ftp\\:\\/\\/)?([a-z0-9\\.]+)(\\:[0-9]+)?(\\/[^?]+)?[\\?]?(.*)?$";

    void parse(const std::string &str);
};


#endif
