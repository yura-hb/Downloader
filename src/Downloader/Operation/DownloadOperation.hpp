#ifndef __DOWNLOAD_OPERATION__
#define __DOWNLOAD_OPERATION__

#include <iostream>
#include <memory>
#include "Operation.hpp"
#include "../../Networking/HTTPClient.hpp"


class DownloadOperation: Operation {
  public:
    DownloadOperation(const std::shared_ptr<HTTPClient> client, const std::string& url) : client(client), url(url) {}
    /**
     * Performs download of the page with the HTTPClient
     */
    bool perform() override;
  private:
    const std::shared_ptr<HTTPClient> client;
    const std::string url;
};

#endif
