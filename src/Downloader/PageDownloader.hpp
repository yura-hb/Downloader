#ifndef __PAGE_DOWNLOADER__
#define __PAGE_DOWNLOADER__

#include <iostream>
#include <vector>
#include <exception>
#include "../Networking/URL.hpp"
#include "../Networking/HTTPClient.hpp"
#include "../FileManager/FileManager.hpp"

class PageDownloader {
  public:
    PageDownloader() {};
    /**
     * Function, which downloads single page all nested parameters and perform save
     */
    virtual void downloadPage(const std::string& url) const;
  private:
    HTTPClient client;
    FileManager fileManager;
    /**
     *  Processes page and returns all references from it.
     *
     *  Input:
     *    @param[in] result - result responce html/css string
     */
    std::vector<std::string> processResponse(const Response& response);
    /**
     *  Saves the file to the relative path from the url
     *
     *  Input:
     *    @param[in] url - string representation of the url
     *    @param[in] data - data to save
     */
    bool save(const std::string& url, const Response& response);
    /**
     *  In case of the wrong request redirection can be asked, so need to perform request again
     */
    void handleRedirection(const Response& response) const;
};

#endif
