#include "Downloader.hpp"

void Downloader::download(const RemoteReference& ref, const LocalReference& filepath) const {
  URL url(ref.requestUrl(""));
  Response response;

  try {
     sendRequest(url, response, true);
  } catch (const Exception& exc) {
     std::cerr << exc.what() << std::endl << std::endl;
  }
}

void Downloader::sendRequest(const URL& url, Response& response, bool followRedirection = true) const {
  Response tmpResponse;

  if (!client.loadPage(url, tmpResponse))
    throw Exception("Request did failed [" + url.requestUrl() + "] (Hint: Socket)");

  if (tmpResponse.status.isRedirection()) {
    if (!followRedirection)
      throw Exception("Can't redirect as protocol is not supported [" + url.requestUrl() + "] (Hint: Redirection)");

    Data<> location = tmpResponse.loadHeader(Header::_Header::LOCATION);

    if (location.empty())
      throw Exception("Can't redirect as location is empty [" + url.requestUrl() + "] (Hint: Redirection)");

    sendRequest(location.stringRepresentation(), response, false);
    return;
  }

  if (tmpResponse.status.isFailed())
    throw Exception("Fail to download [" + url.requestUrl() + "][" + std::to_string(response.status.intCode) + "]");

  response = tmpResponse;
}


void Downloader::save(const Response& response, const LocalReference& filepath) const {
  fileManager.saveFile(filepath, response.loadBody());
}

/**


void Downloader::download(const std::string& url, const LocalReference& filepath) {
  URL uri(url);

  Response response;
  HTMLAnalyzer analyzer;
  bool shouldAddRefs = true;

 // loadQueue.push(uri.requestUrl());

  //loadDomain = uri.domain;

  std::cout << uri.requestUrl() << std::endl;
  try {
     sendRequest(loadQueue.front(), response, true);
     std::cout << response.response << std::endl;
     fileManager.saveFile(LocalReference("test.png"), response.loadBody());
  } catch (const RemoteReference::LinkCreationException& exc) {
     loadQueue.pop();
     shouldAddRefs = false;
    // continue;
  } catch (const Exception& exc) {
     loadQueue.pop();
     shouldAddRefs = false;
     std::cerr << exc.what() << std::endl << std::endl;
    // continue;
  }
/*
  // Don't download file, in case, if preparation failure
  if (!prepare(uri))
    return;

  Response response;
  HTMLAnalyzer analyzer;
  bool shouldAddRefs = true;

  loadQueue.push(uri.requestUrl());

  while (!loadQueue.empty()) {
    response = Response();
    try {
      sendRequest(loadQueue.front(), response, true);
      save(response, response.url.query == "/" ? "/index.html" : "");
    } catch (const RemoteReference::LinkCreationException& exc) {
      loadQueue.pop();
      shouldAddRefs = false;
      continue;
    } catch (const Exception& exc) {
      loadQueue.pop();
      shouldAddRefs = false;
      std::cerr << exc.what() << std::endl << std::endl;
      continue;
    }

    if (shouldAddRefs)
      for (const auto& ref: analyzer.loadReferences(response.body))
        loadQueue.push(ref);

    shouldAddRefs = false;

    std::cout << "Successfully loaded: " << loadQueue.front() << std::endl << std::endl;
    loadQueue.pop();
  }*/
/*}

bool Downloader::prepare(const URL& url) {
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

void Downloader::createSaveFolder(const URL& url) {
  fileManager.createPageFolder(url.domain);
  fileManager.clearDirectory(url.domain);
}

void Downloader::fetchRobotsFile(const URL& url) {
  URL requestUri(url);
  requestUri.query = robotsFileQuery;
  requestUri.parameters = "";
  Response response;

  try {
    sendRequest(requestUri.requestUrl(), response, true);
    save(response);
  } catch (const RemoteReference::LinkCreationException & exc) {
    return;
  } catch (const Exception& exc) {
    std::cerr << exc.what() << std::endl;
  }

  std::cerr << "Fail fetching robots.txt. " << response.status.description()  << std::endl;
}
*/
