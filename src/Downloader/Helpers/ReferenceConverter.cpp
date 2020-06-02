#include "ReferenceConverter.hpp"

const std::string ReferenceConverter::htmlFileContentType = "text/html";
const std::string ReferenceConverter::cssFileContentType = "text/css";

void ReferenceConverter::overwriteReferences(DownloadFileTree& tree, const std::string& mirrorDomain) {
  FileManager fileManager;

  auto overwriteTuple = tree.nextOverwriteReference();

  while (std::get<0>(overwriteTuple) != "") {
    std::shared_ptr<Analyzer> analyzer = loadAnalyzer(std::get<1>(overwriteTuple));

    if (analyzer != nullptr) {
      LocalReference localRef(std::get<0>(overwriteTuple));
      localRef = *dynamic_cast<LocalReference *>(localRef.addAbsoluteReference(mirrorDomain).get());
      LocalReference tmpRef = *dynamic_cast<LocalReference *>(localRef.addFileExtension("old").get());

      analyzer -> overwriteReferences(localRef, tmpRef, [&] (const Data<>& ref) -> Data<> {
        return Data<>("test");
      });
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

std::unique_ptr<Reference> ReferenceConverter::makeReference(const std::string& directoryRef, const std::string& ref, const std::string& mirrorDomain) {
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
