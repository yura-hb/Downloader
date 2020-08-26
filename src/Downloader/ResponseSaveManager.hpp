#ifndef __RESPONSE_SAVE_MANAGER__
#define __RESPONSE_SAVE_MANAGER__

#include "../FileManager/FileManager.hpp"
#include "../Networking/URL.hpp"
#include "../Networking/Response.hpp"
#include "Helpers/ChunkMerger.hpp"

class ResponseSaveManager {
  public:
    /**
     *  @brief
     *    Processes the pure response from the server and saves to the filepath.
     *    In case of successful file save discards the response data.
     *
     *    Processing includes:
     *      * Removing chunk data from the file
     *      * Decoding or encoding data
     *      * Saving of the file to the disk
     *
     *   Input:
     *     @param[in] - response raw response from the server
     *     @param[in] - filepath to save data
     *
     *   Output:
     *     @param[out] response - modifies response and after save the response content is being discared.
     */
    void process(Response& response, const LocalReference& filepath) const;
  private:
    FileManager fileManager;

    static const std::string doubleSeparator;
    static const std::string parameterSeparator;

    /**
     *  @brief
     *    Resolves transfer encoding of the file data downloaded from the server.
     *
     *    There are several of them:
     *      * *identity* - the identity, so no changes should be applied
     *      * *chunked* - the data is splitted on the separate chunks of the next format:
     *        `4-byte-hex-chunk-length \r\n data of chunk length \r\n ...`
     *      * *deflate* - the data is compressed with the zlib algorithm
     *      * *gzip* - the data is compressed gzip compression algorithm
     *
     *    All of these types of compression can be applied several times on the data.
     *    In that case these types are applied by the order, they appear in the response.
     *
     *  Input:
     *    - @param[in] - response, containing headers from the response
     *    - @param[in] - the filepath there the file is saved.
     *
     */
    void resolveTransferEncoding(const Response& response, const LocalReference& filepath) const;
};


#endif
