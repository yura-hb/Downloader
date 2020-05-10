#include "FileDownloader.hpp"

Response FileDownloader::download(const RemoteReference& ref, const LocalReference& filepath) const {
  URL url(ref.requestUrl(""));
  Response response;

  try {
    sendRequest(url, response, true);
    save(response, filepath);
  } catch (const Exception& exc) {
    std::cerr << exc.what() << std::endl << std::endl;
  }

  return response;
}

void FileDownloader::sendRequest(const URL& url, Response& response, bool followRedirection = true) const {
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

void FileDownloader::save(Response& response, const LocalReference& filepath) const {
  saveManager.process(response, filepath);
}
