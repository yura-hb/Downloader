#ifndef __PAGE_DOWNLOADER__
#define __PAGE_DOWNLOADER__

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

class PageDownloader: public Downloader {
  public:
    virtual void download(const RemoteReference& ref, const LocalReference& filepath) const override;

  private:
    std::string loadDomain;

    std::queue<std::string> loadQueue;

    std::unordered_map<std::string, std::string> loadedReferences = {};

    std::set<std::string> lockedReferences = {};

    bool prepare(const URL& url);

    void createSaveFolder(const URL& url);

    void fetchRobotsFile(const URL& url);

    const std::string robotsFileQuery = "/robots.txt";
};

#endif
