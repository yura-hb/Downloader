#include "RemoteReference.hpp"

std::unique_ptr<Reference> RemoteReference::addAbsoleteReference(const std::string& str) const {
  return std::make_unique<RemoteReference>(url);
}

std::unique_ptr<Reference> RemoteReference::addPath(const std::string& str) const {
  URL copy = url;
  copy.query += "/" + str;
  return std::make_unique<RemoteReference>(copy);
}

bool RemoteReference::isDirectory() const {
  return false;
}

bool RemoteReference::isRelative() const {
  return true;
};

std::string RemoteReference::requestUrl(const std::string& domain) const {
  if (url.domain != domain)
    throw LinkCreationException();

  return url.requestUrl();
}

std::string RemoteReference::domain() {
  return url.domain;
}

std::string RemoteReference::query() {
  return url.query;
}
