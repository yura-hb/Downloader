#ifndef __CHUNK_MERGER__
#define __CHUNK_MERGER__

#include <iostream>
#include "../../Templates/Data.hpp"

class ChunkMerger {
  public:
    /**
     *  Discussion:
     *    Merges the chunks and sets them to the body
     *
     *  Input:
     *    - @param[in] body - the chunked body data
     *
     *  Output:
     *    - @param[out] body - the merged body data
     */
    static void mergeChunks(Data<>& body);
  private:
    static std::string separator;
    /**
     *  Discussion:
     *    Reads specific chunk header and erases it from the body.
     *    Returns the length of the chunks.
     *    The format of chunck is the next:
     *      chunk size \r\n chunk data \r\n chunk size \r\n .. \r\n zero chunck size
     *
     *  Input:
     *    - @param[in] body - response in the chunked format
     *
     *  Output:
     *    - @param[out] length of the chunk to read
     */
    static uint32_t readChunkHeader(Data<>& body);
};

#endif
