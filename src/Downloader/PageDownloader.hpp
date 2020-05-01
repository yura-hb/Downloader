#ifndef __PAGE_DOWNLOADER__
#define __PAGE_DOWNLOADER__

#include <iostream>
#include <queue>
#include <memory>
#include <stdexcept>

#include "../Networking/HTTPClient.hpp"

class PageDownloader {
  public:
    PageDownloader() {};
    /**
     * Function, which downloads single page all nested parameters and perform save
     */
    virtual void downloadPage(const std::string& url);
  private:
    /**
     * Performs reguests
     */
    HTTPClient client;
    /**
     *  Processes page
     */
    void processResponse(const std::string& result);
    /**
     *
     */
    
    /**
     *  Loads the page with the HTTPClient
     */
    void load(const std::string& url, const std::string& result);
};

#endif
