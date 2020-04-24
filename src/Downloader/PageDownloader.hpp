#ifndef __PAGE_DOWNLOADER__
#define __PAGE_DOWNLOADER__

#include <iostream>
#include <queue>
#include <memory>

#include "../Networking/HTTPClient.hpp"
#include "Operation/Operation.hpp"
/**
 * # Description
 *   Basic class for downloading one page with the whole resources.
 *
 *   The download is performed in the next states:
 *    1. Download html page, by performing HTTP request
 *    2. Page analysis and lookup for the <link> and <img> tags
 *    3. Download of the css and the images
 *    4. For each downloaded css, save it at the specific reference and check for the images
 */
class PageDownloader {
  public:
    PageDownloader(): client(std::make_shared<HTTPClient>()) {}
    /**
     *  Downloads and saves html page in the folder of the host name
     */
    virtual void download(const std::string& url);

    virtual ~PageDownloader() = default;
  protected:
    // Base
    std::shared_ptr<HTTPClient> client;
    /**
     * This is base operation queue, which is synchronuous.
     * In case of the async solution need to implement some base class to manage operation queue.
     */
    std::queue<std::unique_ptr<Operation>> operationQueue;

    void processOperations();
};

#endif
