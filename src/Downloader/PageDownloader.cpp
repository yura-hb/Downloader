#include "PageDownloader.hpp"

void PageDownloader::mirror(const std::string& url) {
  URL uri(url);

  // Don't download file, in case, if
  if (!prepare(uri) || loadedReferences.find(uri.query) != loadedReferences.end())
    return;

  Response response;

  if (client.loadPage(uri, response) && response.status.isSuccessful()) {
    uri.query += "index.html";
    saveFile(uri, response);

    HTMLAnalyzer analyzer;

    std::vector<Reference> references = analyzer.loadReferences(response.body);

    for (const auto& ref: references)  {
      if (ref.type == Reference::Type::HYPER_LINK) {
        URL componentUri(ref.path);

        std::cout << componentUri.requestUrl() << std::endl;

        if (loadedReferences.find(componentUri.query) == loadedReferences.end() &&
            client.loadPage(componentUri, response) &&
            response.status.isSuccessful()) {

          saveFile(componentUri, response);
        }
      }
    }
    return;
  }
}

bool PageDownloader::prepare(const URL& url) {
  if (!url.isValid()) {
    std::cerr << "Invalid URL: " << url.requestUrl() << std::endl;
    return false;
  }

  try {
    createSaveFolder(url);
    saveFolderReference = Reference(url.domain, Reference::Type::HYPER_LINK);
  } catch (const Exception& exc) {
    std::cerr << exc.what() << std::endl;
    return false;
  }

  fetchRobotsFile(url);
  return true;
}

void PageDownloader::createSaveFolder(const URL& url) {
  fileManager.createPageFolder(url.domain);
  fileManager.clearDirectory(url.domain);
}

void PageDownloader::fetchRobotsFile(const URL& url) {
  URL requestUri(url);
  requestUri.query = robotsFileQuery;
  requestUri.parameters = "";
  Response response;
  //  TODO: - Add redirection
  if (client.loadPage(requestUri, response) && response.status.isSuccessful()) {
    saveFile(requestUri, response);
    return;
  }

  std::cerr << "Fail fetching robots.txt. " << response.status.description()  << std::endl;
}

void PageDownloader::saveFile(const URL& url, const Response& response) {
  fileManager.saveFile(getLocalReference(url), response.body);
  loadedReferences.insert({ url.query, getContentType(response) });
}

Reference PageDownloader::getLocalReference(const URL& url) const {
  return saveFolderReference.addPath(url.query);
}

std::string PageDownloader::getContentType(const Response& response) const {
  auto result = std::find_if(response.headers.begin(), response.headers.end(), [](const Header& header) {
    return header.header == Header::_Header::CONTENT_TYPE;
  });

  return result == response.headers.end() ? "" : result -> parameters;
}
