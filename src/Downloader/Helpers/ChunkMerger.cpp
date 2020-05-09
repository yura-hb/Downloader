#include "ChunkMerger.hpp"

std::string ChunkMerger::separator = "\r\n";
std::string ChunkMerger::temporaryFileExtension = "tmp";

void ChunkMerger::mergeChunks(const LocalReference& filepath) {
  std::unique_ptr<Reference> tmpReference = filepath.addFileExtension(temporaryFileExtension);
  std::string outputPath = dynamic_cast<LocalReference *>(tmpReference.get()) -> getPath();

  std::ifstream in(filepath.getPath(), std::ios::in);
  std::ofstream out(outputPath, std::ios::out | std::ios::trunc);

  if (in.bad())
    throw Exception("Fail to open file");

  if (out.bad())
    throw Exception("Failed to open output file");

  while (in.good()) {
    uint32_t chunkLength = readHeader(in);

    if (chunkLength == 0)
      break;

    Data<> buffer;

    buffer.read(in, chunkLength);
    buffer.write(out, buffer.begin(), buffer.end());
    // Skip the separator between buffer and the chunk length
    if (in.good())
      in.ignore(separator.size());
  }

  std::string command = "mv '" + outputPath + "' '" + filepath.getPath() + "' ";
  std::system(command.c_str());
}

uint32_t ChunkMerger::readHeader(std::ifstream& in) {
  Data<> tmp;
  uint32_t chunkLength = 0;

  tmp.readUntil(in, separator);

  Data<>::iterator end = tmp.end();
  std::advance(end, -(int)separator.size());

  std::string chunkHeader = tmp.subsequence(tmp.begin(), end).stringRepresentation();

  try {
    chunkLength = std::stoul(chunkHeader, nullptr, 16);
  } catch (const std::exception& exc) {
    std::cout << exc.what() << " [Hint: ChunkMerger]" << std::endl;
    return 0;
  }

  return chunkLength;
}
