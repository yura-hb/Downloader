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
  std::string query = "";
  std::string parameters = "";

  URL(const std::string &url);

  bool isValid();

  private:
    /**
     * REGEX description:
     *
     *  1. First group - optional protocol http, ftp, https
     *  2. Server domain group
     *  3. Query - with ending ? symbol
     *  4. Parameters
     *
     */
    const std::string regexString = "^(http\\:\\/\\/|https\\:\\/\\/|ftp\\:\\/\\/)?([a-z0-9\\.]+)(\\:[0-9]+)?(\\/.+\\?)?(.*)+$";

    void parse(const std::string &str);
};


#endif
