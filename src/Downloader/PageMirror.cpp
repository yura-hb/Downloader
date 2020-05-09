#include "PageMirror.hpp"

const std::string PageMirror::robotsFileQuery = "/robots.txt";
const std::string PageMirror::allUsersRobotsLockHeader = "User-agent: *";
const std::string PageMirror::disallowKey = "Disallow";
void PageMirror::mirror(const RemoteReference& ref) {
  prepare(ref);
}

void PageMirror::download(const RemoteReference& ref, const LocalReference& filepath) const {
  FileDownloader::download(ref, filepath);
  // - TODO: - Add analyzer
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

    LocalReference ref(data.stringRepresentation(), true);
    lockedReferences.push_back(ref);

    data = {};
  }

  for (const auto& ref: lockedReferences) {
    std::cout << ref.getPath() << std::endl;
  }
}
