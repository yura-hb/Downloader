#include "RemoteReference.hpp"

std::unique_ptr<Reference> RemoteReference::addAbsoluteReference(const std::string& str) const {
  return std::make_unique<RemoteReference>(url);
}

std::unique_ptr<Reference> RemoteReference::addPath(const std::string& str) const {
  URL copy = url;
  copy.query += "/" + str;
  return std::make_unique<RemoteReference>(copy);
}

std::unique_ptr<Reference> RemoteReference::addFileExtension(const std::string& str) const {
  if (isDirectory())
    throw Exception("Can't add file extension to the directory");

  return std::make_unique<RemoteReference>(path + "." + str);
}

bool RemoteReference::isDirectory() const {
  if (url.query.empty())
    return true;
  return url.query.at(url.query.size() - 1) == '/';;
}

bool RemoteReference::isRelative() const {
  return true;
};

URL RemoteReference::requestUrl(const std::string& domain) const {
  return url;
}

std::string RemoteReference::domain() const {
  return url.domain;
}

std::string RemoteReference::filename() const {
  std::string filename = "";

  if (isDirectory())
    filename = "index.html";

  if (!url.parameters.empty() && isDirectory())
    filename += "?" + url.parameters;

  return filename;
}


std::string RemoteReference::getPath() const {
  if (isDirectory())
    return url.query + filename();

  return url.query;
}

std::string RemoteReference::getDirectoryPath() const {
  if (isDirectory())
    return url.query;

  LocalReference ref(url.query);
  return ref.getDirectoryPath();
}
