#include "PageMirror.hpp"

const std::string PageMirror::robotsFileQuery = "/robots.txt";
const std::string PageMirror::htmlFileContentType = "text/html";
const std::string PageMirror::cssFileContentType = "css/html";
const std::string PageMirror::allUsersRobotsLockHeader = "User-agent: *";
const std::string PageMirror::disallowKey = "Disallow";

void PageMirror::mirror(const RemoteReference& ref) {
  prepare(ref);
  mirrorDomain = ref.domain();
  // TODO - Implement better solution
  std::unique_ptr<Reference> localRef = LocalReference(ref.domain()).addPath(ref.getPath());
  downloadTree.add(std::make_unique<LocalReference>(ref.getPath()));

  LocalReference saveRef = *dynamic_cast<LocalReference *>(localRef.get());
  download(ref, saveRef);
}

Response PageMirror::download(const RemoteReference& ref, const LocalReference& filepath) {
  Response response = FileDownloader::download(ref, filepath);

  for (const auto& header: response.headers)
    std::cout << header.description() << std::endl;

  const Data<> contentType = response.loadHeader(Header::_Header::CONTENT_TYPE);
  std::vector<std::string> references;

  if (contentType == htmlFileContentType) {
    HTMLAnalyzer analyzer;
    references = analyzer.loadReferences(filepath);
  } else if (contentType == cssFileContentType) {
    CSSAnalyzer analyzer;
    references = analyzer.loadReferences(filepath);
  } else {
    return response;
  }

  try {
    for (const std::string& relatedReference: references) {
      URL url(relatedReference);

      if (url.isValid()) {
        if (URL::compareDomains(url.domain, mirrorDomain))
          downloadTree.add(std::make_unique<RemoteReference>(url));
      } else {
        std::unique_ptr<Reference> localRef = std::make_unique<LocalReference>(relatedReference);

        if (localRef -> isRelative())
          downloadTree.add(localRef);
        else
          downloadTree.add(localRef -> addAbsoluteReference(ref.getPath()));
      }
    }

    downloadTree.logTreeDescription();
  } catch (const Exception& exc) {
    std::cerr << exc.what() << std::endl;
  }

  return response;
}

void PageMirror::prepare(const RemoteReference& ref) {
  std::string domain = ref.domain();

  URL url;
  url.domain = domain;
  url.query = robotsFileQuery;

  RemoteReference robotsReference(url);
  LocalReference saveRef = *dynamic_cast<LocalReference *>(LocalReference(domain).addPath(robotsFileQuery).get());

  saveRef.simplify();

  try {
    FileDownloader::download(robotsReference, saveRef);
    processRobotsFile(saveRef);
  } catch (const Exception& exc) {

  }
}

void PageMirror::processRobotsFile(const LocalReference& ref) {
  std::ifstream in(ref.getPath());
  std::string allUsersRobotsLockHeader = "User-agent: *";

  Data<> data;

  data.readUntil(in, allUsersRobotsLockHeader);

  if (!in.good())
    return;

  const std::string newlineSeparator = "\n";
  const std::string directoryStartSeparator = "/";

  data.readUntil(in, newlineSeparator);
  data = {};

  while (in.good()) {
    data.readUntil(in, newlineSeparator);

    auto parameterIter = data.begin();
    auto end = data.end();

    if ((parameterIter = data.find(disallowKey, data.begin())) == data.end())
      break;

    std::advance(parameterIter, disallowKey.size());

    if ((parameterIter = data.find(directoryStartSeparator, parameterIter)) == data.end())
      break;

    std::advance(end, -static_cast<int>(newlineSeparator.size()));

    data = data.subsequence(parameterIter, end);

    try {
      downloadTree.add(std::make_unique<LocalReference>(data.stringRepresentation(), true), true, false);
    } catch (const Exception& exc) {
      std::cerr << exc.what() << std::endl;
    }

    data = {};
  }
}
