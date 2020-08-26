#include "ReferenceConverter.hpp"

const std::string ReferenceConverter::htmlFileContentType = "text/html";
const std::string ReferenceConverter::htmlFileExtension = ".html";
const std::string ReferenceConverter::cssFileContentType = "text/css";


void ReferenceConverter::overwriteReferences(DownloadFileTree& tree, const std::string& mirrorDomain) {
  if (!Configuration::shared.overrideReferences)
    return;

  FileManager fileManager;

  auto overwriteTuple = tree.nextOverwriteReference();

  while (std::get<0>(overwriteTuple) != "") {
    std::shared_ptr<Analyzer> analyzer = loadAnalyzer(std::get<1>(overwriteTuple));
    std::unique_ptr<Reference> ref = nullptr;

    if (analyzer != nullptr && (ref = makeReference("/", std::get<0>(overwriteTuple), mirrorDomain)) != nullptr) {

      try {
        std::unique_ptr<Reference> localRef = ref -> addAbsoluteReference(mirrorDomain);
        std::unique_ptr<Reference> tmpRef = localRef -> addFileExtension("old");

        bool isValidReference = dynamic_cast<LocalReference *>(localRef.get()) != nullptr &&
                                dynamic_cast<LocalReference *>(tmpRef.get()) != nullptr &&
                                !localRef -> isDirectory() && !tmpRef -> isDirectory();

        if (isValidReference) {
          fileManager.rename(localRef -> getPath(), tmpRef -> getPath());

          addHtmlFileExtensionIfNeeded(std::get<1>(overwriteTuple), localRef);

          analyzer -> overwriteReferences(tmpRef -> getPath(), localRef -> getPath(), [&] (const Data<>& reference) -> Data<> {
            return convertReference(ref, tree, mirrorDomain, reference);
          });

          if (Configuration::shared.removedOriginFiles)
            fileManager.remove(tmpRef -> getPath());
        }
      } catch (const Exception& exc) {
        Logger::logError(exc);
      }
    }

    tree.setOverwritten(LocalReference(std::get<0>(overwriteTuple)));
    overwriteTuple = tree.nextOverwriteReference();
  }
}

void ReferenceConverter::analyze(const RemoteReference& downloadRef,
                                 const LocalReference& filepath,
                                 const std::string& mirrorDomain,
                                 const Data<>& contentType,
                                 DownloadFileTree& tree) {
  std::vector<std::string> references = loadReferences(filepath, contentType);

  try {
    std::string directoryRef = downloadRef.getDirectoryPath();

    for (const std::string& ref: references) {
      auto itemRef = makeReference(directoryRef, ref, mirrorDomain);

      if (itemRef != nullptr)
        tree.add(*(itemRef.get()), false, false);
    }

  } catch (const Exception& exc) {
    Logger::logError(exc);
  }
}

std::vector<std::string> ReferenceConverter::loadReferences(const LocalReference& filepath, const Data<>& contentType) {
  std::shared_ptr<Analyzer> analyzer = loadAnalyzer(contentType);

  if (analyzer != nullptr)
    return analyzer -> loadReferences(filepath);

  return {};
}

std::unique_ptr<Reference> ReferenceConverter::makeReference(const std::string& directoryRef,
                                                             const std::string& ref,
                                                             const std::string& mirrorDomain) {
  URL url(ref);

  if (url.isValid()) {
    if (URL::compareDomains(url.domain, mirrorDomain))
      return std::make_unique<RemoteReference>(RemoteReference(url));
  } else {
    std::unique_ptr<LocalReference> localRef = std::make_unique<LocalReference>(ref);

    if (localRef -> isRelative())
      return localRef;
    else
      return localRef -> addAbsoluteReference(directoryRef);
  }

  return nullptr;
}
std::shared_ptr<Analyzer> ReferenceConverter::loadAnalyzer(const Data<>& contentType) {
  std::shared_ptr<Analyzer> analyzer = nullptr;

  if (contentType.find(htmlFileContentType, contentType.begin()) != contentType.end()) {
    analyzer = std::make_shared<HTMLAnalyzer>();
  } else if (contentType.find(cssFileContentType, contentType.begin()) != contentType.end()) {
    analyzer = std::make_shared<CSSAnalyzer>();
  }

  return analyzer;
}

Data<> ReferenceConverter::convertReference(const std::unique_ptr<Reference>& processingFile,
                                            DownloadFileTree& tree,
                                            const std::string& mirrorDomain,
                                            const Data<>& ref) {
  std::unique_ptr<Reference> reference = makeReference(processingFile -> getDirectoryPath(), ref.string(), mirrorDomain);

  bool isConvertable = dynamic_cast<LocalReference *>(reference.get()) != nullptr;

  if (isConvertable) {
    State state;

    try {
      state = tree.loadState(*reference.get());
    } catch (const Exception& exc) {
      Logger::logError(exc);
      return ref;
    }

    if (state.isDownloaded) {
      std::string directoryPath = processingFile -> getDirectoryPath();
      Data<> filePath = reference -> getPath();

      if (filePath.beginsWith(directoryPath)) {
        filePath.eraseFirst(directoryPath, filePath.begin());

        addHtmlFileExtensionIfNeeded(state, filePath);

        return filePath;
      } else {
        // In case, if it is root folder and the file without obsolete reference, then no changes needed
        if (directoryPath == "/")
          return filePath;
        // In case, if the some file referencing the file using root reference,
        // then simply move to the root reference, by adding .. and then add file path.
        uint8_t depth = 0;

        for (const auto& c: directoryPath)
          if (c == '/')
            depth++;

        if (depth > 0)
          depth--;

        Data<> updatedFilePath;

        for (uint8_t i = 0; i < depth; i++)
          updatedFilePath.append("..");

        updatedFilePath.append(filePath);

        addHtmlFileExtensionIfNeeded(state, updatedFilePath);

        return updatedFilePath;
      }

    } else {
      // In case, if reference is not downloaded, create a link to it.
      URL url;

      url.protocol = url.http;
      url.domain = mirrorDomain;
      url.query = reference -> getPath();

      return url.requestUrl();
    }
  }

  return ref;
}

void ReferenceConverter::addHtmlFileExtensionIfNeeded(const State& state, Data<>& ref) {
  if (!Configuration::shared.fixHtmlPathes)
    return;

  Data<> contentType = state.contentType;

  if (contentType.find(htmlFileContentType, contentType.begin()) != contentType.end() && !ref.endsWith(htmlFileExtension))
    ref.append(htmlFileExtension);
}

void ReferenceConverter::addHtmlFileExtensionIfNeeded(const Data<> contentType, std::unique_ptr<Reference>& ref) {
  if (!Configuration::shared.fixHtmlPathes)
    return;

  Data<> refPath = ref -> getPath();

  if (contentType.find(htmlFileContentType, contentType.begin()) != contentType.end() && !refPath.endsWith(htmlFileExtension)) {
    Data<> fileExtension = htmlFileExtension;
    fileExtension.popFirst();

    ref = ref -> addFileExtension(fileExtension.string());
  }
}
