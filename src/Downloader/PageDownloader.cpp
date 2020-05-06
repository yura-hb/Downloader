#include "PageDownloader.hpp"

void PageDownloader::mirror(const std::string& url) {
  URL uri(url);

  // Don't download file, in case, if preparation failure
  if (!prepare(uri))
    return;

  Response response;
  HTMLAnalyzer analyzer;
  bool shouldAddRefs = true;

  loadQueue.push(uri.requestUrl());

  while (!loadQueue.empty()) {
    try {
      sendRequest(loadQueue.front(), response, true);
      save(response, response.url.query == "/" ? "/index.html" : "");
    } catch (const PageDownloaderException& exc) {
      loadQueue.pop();
      shouldAddRefs = false;
      continue;
    } catch (const Exception& exc) {
      loadQueue.pop();
      shouldAddRefs = false;
      std::cerr << exc.what() << std::endl;
      continue;
    }

    if (shouldAddRefs)
      for (const auto& ref: analyzer.loadReferences(response.body))
        loadQueue.push(ref);

    shouldAddRefs = false;

    std::cout << "Successfully loaded: " << loadQueue.front() << std::endl;
    loadQueue.pop();
  }
}

bool PageDownloader::prepare(const URL& url) {
  if (!url.isValid()) {
    std::cerr << "Invalid URL: " << url.requestUrl() << std::endl;
    return false;
  }

  try {
    createSaveFolder(url.domain);
    loadDomain = url.domain;
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

  try {
    sendRequest(requestUri.requestUrl(), response, true);
    save(response);
  } catch (const PageDownloaderException & exc) {
    return;
  } catch (const Exception& exc) {
    std::cerr << exc.what() << std::endl;
  }

  std::cerr << "Fail fetching robots.txt. " << response.status.description()  << std::endl;
}

void PageDownloader::sendRequest(const std::string& link,
                                 Response& response,
                                 bool followRedirection = true) const {
  std::shared_ptr<Reference> reference = ReferenceConverter::convert(link);

  URL url;

  try {
    url = ReferenceConverter::makeRequest(loadDomain, reference);
  } catch (const Exception& e) {
    return;
  }

  if (url.domain != loadDomain)
    throw PageDownloaderException();

  sendRequest(url, response, followRedirection);
}

void PageDownloader::sendRequest(const URL& url,
                                 Response& response,
                                 bool followRedirection = true) const {
  Response tmpResponse;

  if (!client.loadPage(url, tmpResponse))
    throw Exception("Request did failed [" + url.requestUrl() + "] (Hint: Socket)");

  if (tmpResponse.status.isRedirection()) {
    if (!followRedirection)
      throw Exception("Can't redirect as protocol is not supported [" + url.requestUrl() + "] (Hint: Redirection)");

    std::string location = response.loadHeader(Header::_Header::LOCATION);

    if (location.empty())
      throw Exception("Can't redirect as location is empty [" + url.requestUrl() + "] (Hint: Redirection)");

    sendRequest(location, tmpResponse, false);
    return;
  }

  if (tmpResponse.status.isFailed())
    throw Exception("Fail to download [" + url.requestUrl() + "][" + std::to_string(response.status.intCode) + "]");

  response = tmpResponse;
}

void PageDownloader::save(const Response& response, const std::string& filepath) const {
  std::string path;

  if (filepath.empty())
    path = response.url.query + (response.url.parameters.empty() ? "" : ("?" + response.url.parameters));
  else
    path = filepath;

  LocalReference ref(loadDomain);
  ref = *dynamic_cast<LocalReference*>(ref.addPath(path).get());
  fileManager.saveFile(ref, response.body);
}
