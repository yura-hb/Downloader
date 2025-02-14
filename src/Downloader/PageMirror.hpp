#ifndef __PAGE_MIRROR__
#define __PAGE_MIRROR__

#include <vector>
#include <exception>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <queue>

#include "FileDownloader.hpp"

#include "../Base/Data.hpp"

#include "../Networking/URL.hpp"
#include "../Networking/HTTPClient.hpp"

#include "../FileManager/FileManager.hpp"

#include "Helpers/DownloadFileTree.hpp"
#include "Helpers/ReferenceConverter.hpp"

/**
 *  Downloader, which will be responsible for mirroring the page and all it underlying sources.
 */
class PageMirror: public FileDownloader {
  public:
    /**
     *  Input:
     *   @param[in] depth - the depth of the recursive download.
     *   @param[in] style - the traverse style.
     *
     */
    PageMirror(int maximalDepth = 100, DownloadFileTree::TraverseStyle style = DownloadFileTree::TraverseStyle::BREADTH_FIRST_SEARCH):
      FileDownloader(),
      downloadTree(DownloadFileTree(maximalDepth, style)) {};

    virtual ~PageMirror() = default;
    /**
     * @brief
     *   Download is taken in several steps.
     *
     *   1. Download the robots.txt file and extract from it all locked references
     *   2. Download the file from the remote reference and if it is html file or css file extract the references
     *   3. For each reference download its underlying source. In case of the html or css repeat the step 2.
     *
     *   !!! Don't download the files out of the remote domain
     *
     * Input:
     *   @param[in] ref - link to the page, which content is needed to be mirrored..
     *
     */
    virtual void mirror(const RemoteReference& ref);
    /**
     * @brief
     *   Downloads specific file with setting references.
     *
     * Input:
     *   @param[in] ref - link to the page, which content is needed to be mirrored.
     *   @param[in] filepath - reference to the local folder, to which should the files be saved.
     *
     */
    virtual Response download(const RemoteReference& ref,
                              const LocalReference& filepath) override;
  protected:
    /**
     * Model for storing info about the Request and download position
     */
    struct Request {
      RemoteReference ref;
      int depth = 0;
    };
    /**
     * @brief
     *   Load queue for requests
     */
    std::queue<Request> loadQueue;
    /**
     * @brief
     *   As mirroring is done only be one site domain, need to hold mirror domain
     */
    std::string mirrorDomain;
    /**
     * @brief
     *   Download file tree
     */
    DownloadFileTree downloadTree;
    /**
     * @brief
     *   Prepares before mirroring the web site: sets the locked reference and downloads robots.txt
     */
    void prepare(const RemoteReference& ref);
    /**
     * @brief
     *   Processes robots.txt file and sets locked reference dict
     */
    void processRobotsFile(const LocalReference& ref);

    static const std::string robotsFileQuery;
    static const std::string allUsersRobotsLockHeader;
    static const std::string disallowKey;
};

#endif
