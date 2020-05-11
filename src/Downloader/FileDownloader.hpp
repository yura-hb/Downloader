#ifndef __FILE_DOWNLOADER__
#define __FILE_DOWNLOADER__

#include <iostream>
#include <vector>
#include <exception>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <queue>

#include "ResponseSaveManager.hpp"
#include "../Base/Data.hpp"
#include "../Networking/URL.hpp"
#include "../Networking/HTTPClient.hpp"
#include "../FileManager/Models/RemoteReference.hpp"
#include "../FileManager/Models/LocalReference.hpp"
/**
 *  Simple downloader, which will proceed download, processing and save of the file
 */
class FileDownloader {
  public:
    FileDownloader() {};
    virtual ~FileDownloader() {};
    /**
     *  Discussion:
     *    Downloads the file and saves it on the specific filepath. The filepath should contain filename
     *
     *  Input:
     *    @param[in] url - string representation of the url
     *    @param[in] filepath - relative reference from the current directory where to save file
     *
     *  Output:
     *    @param[out] - response object containing headers
     *
     */
    virtual Response download(const RemoteReference& ref, const LocalReference& filepath);
  protected:
    HTTPClient client;
    ResponseSaveManager saveManager;
    /**
     *  Discussion:
     *    Commit the request cycle with the possible redirection and returns response
     *
     *  Input:
     *    @param[in] link - URL object
     *    @param[in] response  - response model
     *    @param[in] follow redirection - boolean flag, which indicating, if the file should be redirected
     *
     *  Output:
     *    @param[out] - filled response
     *
     *  Throws:
     *    Throws Exception object on the any error during download
     */
    void sendRequest(const URL& url, Response& response, bool followRedirection) const;
    /**
     *  Discussion:
     *    Saves the response object on the specific filepath.
     *    In case of successful save the response data is being discarded, as can be accessed from the file at the filepath.
     *
     *  Input:
     *    @param[in] response - filled respons object
     *    @param[in] filepath - filepath, where to save the object
     *
     */
    void save(Response& response, const LocalReference& filepath) const;
};

#endif
