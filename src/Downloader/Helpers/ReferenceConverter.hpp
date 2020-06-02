#ifndef __REFERENCE_CONVERTER_H__
#define __REFERENCE_CONVERTER_H__

#include <iostream>

#include "../../Base/Data.hpp"
#include "../../Base/Logger.hpp"

#include "../../FileManager/FileManager.hpp"
#include "../../FileManager/Models/RemoteReference.hpp"

#include "DownloadFileTree.hpp"

#include "../../SyntaxAnalyzer/HTMLAnalyzer.hpp"
#include "../../SyntaxAnalyzer/CSSAnalyzer.hpp"

class ReferenceConverter {
  public:
    /**
     *  @brief
     *    Reference converting process is done by the analyzing the downloaded file and the mirrored file structure.
     *
     *    There are several cases to handle:
     *
     *      1. Relative(obsolete references) should be converted to the reference in the download folder.
     *
     *      2. In case, if the download has failed for the specific file we set its reference on the remote, just by adding domain url
     *
     *      3. References in the current directory should be left as normal
     *
     *      4. The servers generally don't use file extension for the .html files,
     *         the problem is that such files doesn't work normally on the local machine.
     *         The solution should add file extension, if needed.
     *
     *  @param[in] tree - the tree with the downloaded files
     *  @param[in] mirrorDomain - the domain, which is mirrored
     */
    static void overwriteReferences(DownloadFileTree& tree, const std::string& mirrorDomain);
    /**
     *  @brief
     *    Analyzes the file at the file path and adds references to the download file tree
     *
     *  @param[in] downloadRef - reference for downloading file
     *  @param[in] filepath - reference to the file from the current directory.
     *  @param[in] mirrorDomain - the domain, for which mirroring occurs.
     *  @param[in] contentType - the content type of the file from HTML response headers.
     *  @param[in] tree - download file tree.
     *
     */
    static void analyze(const RemoteReference& downloadRef,
                        const LocalReference& filepath,
                        const std::string& mirrorDomain,
                        const Data<>& contentType,
                        DownloadFileTree& tree);
  private:
    static const std::string htmlFileContentType;
    static const std::string cssFileContentType;

    static std::vector<std::string> loadReferences(const LocalReference& filepath, const Data<>& contentType);

    static std::unique_ptr<Reference> makeReference(const std::string& directoryRef, const std::string& ref, const std::string& mirrorDomain);

    static std::shared_ptr<Analyzer> loadAnalyzer(const Data<>& contentType);
};

#endif
