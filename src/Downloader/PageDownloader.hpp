#ifndef __PAGE_DOWNLOADER__
#define __PAGE_DOWNLOADER__

#include <iostream>
#include <vector>
#include <exception>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include "../Networking/URL.hpp"
#include "../Networking/HTTPClient.hpp"
#include "../FileManager/FileManager.hpp"

/**
 * Base class to download html page and all it underlying resources.
 *
 * Prepare:
 *   1. Try to download robots.txt and extract dissallowed pathes
 *   2. Create download folder.
 *
 * The general pipeline of the downloading:
 *   1. Download index.html page file by performing HTTP Get Request
 *   2. Parse headers and status of the request.
 *
 *   There are several outcomes:
 *     * Success
 *         1. Extract the data type from the header
 *         2. In case, if it is text/html or text/css, extract from file hyperlinks references.
 *            Otherwise, save file from the url query and name
 *         3. Add all hyperlinks references to the downloading queue
 *         4. Continue download for all items
 *     * Redirection error (Codes: 30x):
 *         1. Extract link from the redirection headers
 *         2. Perform request with the new link
 *         3. In case of any error - end execution. (As support only HTTP, redirection can end in infinite recursion)
 *     * Failure (Codes: 40x - 500x):
 *            Log the error and continue
 */
class PageDownloader {
  public:
    PageDownloader() {};
    virtual ~PageDownloader() {};

    virtual void mirror(const std::string& url);

  protected:
    Reference saveFolderReference;
    // Clients
    HTTPClient client;
    FileManager fileManager;

    std::queue<std::string> requests;
    /**
     * Set of all downloaded references
     */
    std::unordered_map<std::string, std::string> loadedReferences = {};
    /**
     * Set of locked, references, from it is clear, that the load will failure
     */
    std::set<std::string> lockedReferences = {};

    bool prepare(const URL& url);

    void createSaveFolder(const URL& url);
    
    void saveFile(const URL& url, const Response& response);

    void fetchRobotsFile(const URL& url);

    Reference getLocalReference(const URL& url) const;
    // Helpers

    std::string getContentType(const Response& response) const;
  private:
    const std::string robotsFileQuery = "/robots.txt";
};

#endif
