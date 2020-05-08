#ifndef __DOWNLOADER__
#define __DOWNLOADER__

#include <vector>
#include <exception>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <queue>

#include "../Templates/Data.hpp"
#include "../Networking/URL.hpp"
#include "../Networking/HTTPClient.hpp"
#include "../FileManager/FileManager.hpp"
#include "../FileManager/Models/RemoteReference.hpp"
/**
 *  Simple downloader, which will proceed download, processing and save of the file
 */
class Downloader {
  public:
    Downloader() {};
    virtual ~Downloader() {};
    /**
     *  Discussion:
     *    Downloads the file and saves it on the specific filepath. The filepath should contain filename
     *
     *  Input:
     *    @param[in] url - string representation of the url
     *    @param[in] filepath - relative reference from the current directory where to save file
     *
     */
    virtual void download(const RemoteReference& ref, const LocalReference& filepath) const;
  protected:
    HTTPClient client;
    FileManager fileManager;
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
     *    Saves the response object on the specific filepath
     *
     *  Input:
     *    @param[in] response - filled respons object
     *    @param[in] filepath - filepath to save the object
     *
     */
    void save(const Response& response, const LocalReference& filepath) const;
};

#endif
