#include "ResponseSaveManager.hpp"

const std::string ResponseSaveManager::doubleSeparator = "\r\n\r\n";
const std::string ResponseSaveManager::parameterSeparator = ", ";

void ResponseSaveManager::process(Response& response, const LocalReference& filepath) const {
  if (filepath.isDirectory())
    throw Exception("Can't work on the directory");

  auto bodyStartPosition = response.response.find(doubleSeparator, response.response.begin());
  std::advance(bodyStartPosition, doubleSeparator.size());

  try {
    fileManager.saveFile(filepath, response.response, bodyStartPosition);

    response.response = {};

    resolveTransferEncoding(response, filepath);
  } catch (const Exception& exc) {
    std::cerr << exc.what() << std::endl;
    return;
  }
}

void ResponseSaveManager::resolveTransferEncoding(const Response& response, const LocalReference& filepath) const {
  Data<> transferEncoding = response.loadHeader(Header::_Header::TRANSFER_ENCODING);

  transferEncoding.forEachInterval(parameterSeparator, [&](const Data<>& data) {
    try {
      if (data == "chunked") {
        ChunkMerger::mergeChunks(filepath);
      } else if (data == "gzip") {

      } else if (data == "deflate") {

      } else {
        return;
      }
    } catch (const Exception& exc) {
      std::cerr << exc.what() << std::endl;
    }
  });
}

void ResponseSaveManager::overwriteReferences(const Response& response, const LocalReference& filepath) const {

}

/*
Data<> Response::loadBody() const {
  auto bodyBegin = response.find(doubleSeparator, response.begin());
  std::advance(bodyBegin, doubleSeparator.size());
  Data<> body = response.subsequence(bodyBegin, response.end());

  processTransferEncoding(body);

  Data<> contentType = loadHeader(Header::_Header::CONTENT_TYPE);

  if (std::mismatch(textContentTypePrefix.begin(),
                    textContentTypePrefix.end(),
                    contentType.begin(),
                    contentType.end()).first == textContentTypePrefix.end()) {
    // Convert from CRLF to LF to unix separator(LF)
    #ifdef unix
    #endif
  }

  return body;
}
void Response::processTransferEncoding(Data<>& body) const {
  Data<> transferEncoding = loadHeader(Header::_Header::TRANSFER_ENCODING);

  if (transferEncoding.empty())
    return;

  transferEncoding.forEachInterval(headerParametersSeparator, [&body, this](const Data<>& data) {
    std::cout << data.stringRepresentation() << std::endl;
    switch (transferEncodingType(data)) {
    case (Response::TransferEncodingType::CHUNCKED):
      ChunkMerger::mergeChunks(body);
      break;
    case (Response::TransferEncodingType::GZIP):
      break;
    default: break;
    }
  });
}

Response::TransferEncodingType Response::transferEncodingType(const Data<>& data) const {
  if (data == "chunked") {
    return Response::TransferEncodingType::CHUNCKED;
  } else if (data == "gzip") {
    return Response::TransferEncodingType::GZIP;
  } else {
    return Response::TransferEncodingType::IDENTITY;
  }
}
*/
