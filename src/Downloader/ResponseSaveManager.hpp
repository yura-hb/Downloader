#ifndef __RESPONSE_SAVE_MANAGER__
#define __RESPONSE_SAVE_MANAGER__

#include "../FileManager/FileManager.hpp"
#include "../Networking/URL.hpp"
#include "../Networking/Response.hpp"

class ResponseSaveManager {
  public:
    /**
     *  Discussion:
     *    Processes the pure response from the server and saves to the filepath.
     *
     *    Processing includes:
     *      * Removing chunk data from the file
     *      * Decoding or encoding data
     *      * Saving of the file to the disk
     *
     *   Input:
     *     @param[in] - response raw response from the server
     *     @param[in] - filepath to save data
     */
    void process(const Response& response, const LocalReference& filepath) const;
    /**
     *  Discussion:
     *    If response is the text/html or text/css content type, overwrite local references with
     *    the links.
     *    !!! Important, this is done in the blindfold way without validating, if the file thr file exists on the disk or not
     *    TODO: - Think of better solution
     *
     *  Input:
     *    @param[in] - response raw response from the server
     *    @param[in] - filepath to save data
     */
    void overwriteReferences(const Response& response, const LocalReference& filepath) const;
  private:
    FileManager fileManager;

    const std::string Response::headerParametersSeparator = ", ";
    const std::string Response::textContentTypePrefix = "text/";
};


#endif
