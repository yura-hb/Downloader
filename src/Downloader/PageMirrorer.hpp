#ifndef __PAGE_MIRRORER__
#define __PAGE_MIRRORER__

#include <vector>
#include <exception>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <queue>

#include "Downloader.hpp"

#include "../Templates/Data.hpp"

#include "../Networking/URL.hpp"
#include "../Networking/HTTPClient.hpp"

#include "../SyntaxAnalyzer/HTMLAnalyzer.hpp"

#include "../FileManager/FileManager.hpp"
#include "../FileManager/Models/ReferenceConverter.hpp"

/**
 *  Downloader, which will be responsible for mirroring the page and all it underlying sources.
 */
class PageMirrorer: public Downloader {
  public:
    /**
     *  Input:
     *   @param[in] depth - the depth of the recursive download.
     *
     */
    PageMirrorer(int maximalDepth = 1): maximalDepth(maximalDepth) {};
    virtual ~PageMirrorer() = default;
    /**
     * Discussion:
     *   Download is taken in several steps.
     *
     *   1. Download the robots.txt file and extract from it all locked references
     *   2. Download the file from the remote reference and if it is html file or css file extract the references
     *   3. For each reference download its underlying source. In case of the html or css repeat the step 2.
     *
     *   !!! Don't download the files out of the remote domain
     *
     * Input:
     *   @param[in] ref - link to the page, which content is needed to be mirrored.
     *   @param[in] filepath - reference to the local folder, to which should the files be saved.
     *
     */
    virtual void mirror(const RemoteReference& ref,
                        const LocalReference& filepath) const;
    /**
     * Discussion:
     *   Downloads specific file with setting references.
     *
     * Input:
     *   @param[in] ref - link to the page, which content is needed to be mirrored.
     *   @param[in] filepath - reference to the local folder, to which should the files be saved.
     *
     */
    virtual void download(const RemoteReference& ref,
                          const LocalReference& filepath) const override;
  protected:
    /**
     * Model for storing info about the Request and download position
     */
    struct Request {
      RemoteReference ref;
      int depth = 0;
    };
    /**
     * Discussion:
     *   Maximum allowed depth for download, otherwise wouldn't download anything.
     */
    int maximalDepth = 1;
    /**
     * Discussion:
     *   Load queue for requests
     */
    std::queue<Request> loadQueue;
    /**
     * Discussion:
     *   Already loaded references
     */
    std::unordered_map<const Request, const LocalReference> loadedReferences = {};
    /**
     * Discussion:
     *   References, which are locked by the server
     */
    std::set<const LocalReference> lockedReferences = {};
    /**
     * Discussion:
     *   Prepares before mirroring the web site: sets the locked reference and downloads robots.txt
     */
    bool prepare(const RemoteReference& url);

    const std::string robotsFileQuery = "/robots.txt";
};

#endif
