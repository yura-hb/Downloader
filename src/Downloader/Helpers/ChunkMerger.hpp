#ifndef __CHUNK_MERGER__
#define __CHUNK_MERGER__

#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>

#include "../../Base/Data.hpp"
#include "../../FileManager/Models/LocalReference.hpp"

class ChunkMerger {
  public:
    /**
     *  Discussion:
     *    Processes the file at the file path and removes the chunk separation in it.
     *
     *  Input:
     *    - @param[in] filepath - the path to the file with the filepath.
     *
     *  Throws:
     *    Throws the exception, in case, if file operation were failed
     *
     */
    static void mergeChunks(const LocalReference& filepath);
  private:
    static std::string separator;
    static std::string temporaryFileExtension;

    static uint32_t readHeader(std::ifstream& in);
};

#endif
