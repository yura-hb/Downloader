#include "LocalReference.hpp"

std::unique_ptr<Reference> LocalReference::addAbsoluteReference(const std::string& str) const {
  if (isRelative())
    return std::make_unique<LocalReference>(str + path, true);
  return std::make_unique<LocalReference>(str + "/" + path, true);
}

std::unique_ptr<Reference> LocalReference::addPath(const std::string& str) const {
  if (isDirectory())
    return std::make_unique<LocalReference>(path + str, true);

  return std::make_unique<LocalReference>(path + "/" + str,  true);
}

std::unique_ptr<Reference> LocalReference::addFileExtension(const std::string& str) const {
  return std::make_unique<LocalReference>(path + "." + str);
}

bool LocalReference::isDirectory() const {
  if (path.empty())
    return true;
  return path.at(path.size() - 1) == '/';
}

bool LocalReference::isRelative() const {
  return *path.begin() == '/';
}

std::string LocalReference::getPath() const {
  return path;
}

std::string LocalReference::filename() const {
  size_t separatorPosition = 0;
  std::string separator = "/";

  if (isDirectory() || (separatorPosition = path.rfind(separator)) != std::string::npos)
    throw Exception("Is directory. [Hint: Local reference]");

  separatorPosition += separator.size();

  return path.substr(separatorPosition);
}

URL LocalReference::requestUrl(const std::string& domain) const {
  URL url;
  url.protocol = URL::Protocol::http;
  url.query = path;
  url.domain = domain;

  return url;
}

std::list<std::string> LocalReference::loadComponents() const {
  // TODO - Remove as better implement with DATA
  std::list<std::string> list;

  auto begin = path.begin();
  auto next = path.begin();

  while ((next = std::find(begin, path.end(), '/')) != path.end()) {
    list.push_back(std::string(begin, next));
    begin = next + 1;
  }

  list.push_back(std::string(begin, path.end()));
  return list;
}

void LocalReference::simplify() {
  std::list<std::string> components = loadComponents();

  auto accumulator = [this, components](std::string result, std::string& component) {
    if (component == "" || component == ".")
      return result;

    // In this case, remove previous reference
    if (component == "..") {
      auto iter = result.rbegin();
      if ((iter = std::find(result.rbegin(), result.rend(), '/')) != result.rend()) {
        int offset = result.rend() - iter;
        return std::string(result.begin(), result.begin() + offset);
      }
      return std::string();
    }
    if (result == "/" && isRelative())
      return std::move(result) + component;

    return std::move(result) + component + "/";
  };

  bool isDirectoryPath = isDirectory();
  std::string prefix = isRelative() ? "/" : "";
  path = prefix + std::accumulate(components.begin(), components.end(), std::string(), accumulator);

  if (path.at(path.size() - 1) == '/')
    path.at(path.size() - 1) = isDirectoryPath ? '/' : ' ';
}
