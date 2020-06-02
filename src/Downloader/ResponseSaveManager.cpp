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
    Logger::logError(exc);
    return;
  }
}

void ResponseSaveManager::resolveTransferEncoding(const Response& response, const LocalReference& filepath) const {
  Data<> transferEncoding = response.loadHeader(Header::_Header::TRANSFER_ENCODING);

  transferEncoding.forEachInterval(parameterSeparator, [&](const Data<>& data) {
    try {
      if (data == "chunked") {
        ChunkMerger::mergeChunks(filepath);
      } else {
        return;
      }
    } catch (const Exception& exc) {
      Logger::logError(exc);
    }
  });
}
