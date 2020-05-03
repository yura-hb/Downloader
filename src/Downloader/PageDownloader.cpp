#include "PageDownloader.hpp"

void PageDownloader::downloadPage(const std::string& url) const {
  URL uri(url);
  //  - Create folder
  try {
    fileManager.createPageFolder(uri.domain);
  } catch (FileManager::Exception& exception) {
    // TODO: - Ask user, if he wants to continue
    std::cerr << exception.what() << std::endl;
  }

  Response response;

  if (client.loadPage(url, response)) {
    if (response.status.intCode >= 300 && response.status.intCode < 400)
      handleRedirection(response);
    return;
  }

}

std::vector<std::string> PageDownloader::processResponse(const Response& response) {

}

bool PageDownloader::save(const std::string& url, const Response& response) {

}

void PageDownloader::handleRedirection(const Response& response) const {
  // TODO: - Implement redirection
}
