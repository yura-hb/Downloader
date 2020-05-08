#include "ChunkMerger.hpp"

std::string ChunkMerger::separator = "\r\n";

void ChunkMerger::mergeChunks(Data<>& body) {
  Data<> bodyData;
  uint32_t chunkLength = 0;

  while ((chunkLength = readChunkHeader(body))) {
    auto chunkBegin = body.begin();
    auto chunkEnd = body.at(chunkLength);
    bodyData.append(body.subsequence(chunkBegin, chunkEnd));
    // Advance chunk size on the separator size to begin with the new chunk
    std::advance(chunkEnd, separator.size());
    body.eraseSequence(chunkBegin, chunkEnd);
  }

  body = bodyData;
}

uint32_t ChunkMerger::readChunkHeader(Data<>& body) {
  auto chunkHeaderEnd = body.find(separator, body.begin());
  std::string chunkHeader = body.subsequence(body.begin(), chunkHeaderEnd).stringRepresentation();

  uint32_t chunkLength = 0;

  try {
    chunkLength = std::stoul(chunkHeader, nullptr, 16);
  } catch (const std::exception& exc) {
    std::cout << exc.what() << " [Hint: ChunkMerger]" << std::endl;
    return 0;
  }

  std::advance(chunkHeaderEnd, separator.size());
  body.eraseSequence(body.begin(), chunkHeaderEnd);

  return chunkLength;
}
