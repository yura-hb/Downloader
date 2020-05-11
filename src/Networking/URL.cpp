#include "URL.hpp"

const std::string URL::httpPrefix = "http://";
const std::string URL::httpsPrefix = "https://";
const std::string URL::ftpPrefix = "ftp://";
const std::string URL::wwwPrefix = "www.";

URL::URL(const std::string &url) {
  parse(url);
}

std::string URL::requestUrl() const {
  std::string result = "";

  switch (protocol) {
    case Protocol::http:
      result += "http://";
      break;
    case Protocol::https:
      result += "https://";
      break;
    case Protocol::ftp:
      result += "ftp://";
    case Protocol::undefined:
      result += "";
  }

  result += domain + query;

  if (parameters != "")
    result += "?" + parameters;

  return result;
}

bool URL::isValid() const {
  return protocol != Protocol::undefined &&
    !domain.empty() &&
    domain.find(".") != domain.npos &&
    std::any_of(domain.begin(), domain.end(), [](char c) { return isalpha(c); });
}

void URL::parse(const std::string &urlString) {
  Data<> url = urlString;

  if (url.beginsWith(httpPrefix)) {
    url.eraseFirst(httpPrefix, url.begin());
    protocol = Protocol::http;
  } else if (url.beginsWith(httpsPrefix)) {
    url.eraseFirst(httpsPrefix, url.begin());
    protocol = Protocol::https;
  } else if (url.beginsWith(ftpPrefix)) {
    url.eraseFirst(ftpPrefix, url.begin());
    protocol = Protocol::ftp;
  } else {
    protocol = Protocol::http;
  }

  std::vector<uint8_t> separators = { '/', '?' };

  auto begin = url.begin();

  while (begin != url.end()) {
    auto separatorIndex = separators.begin();
    if ((separatorIndex = std::find(separators.begin(), separators.end(), *begin)) != separators.end()) {
      if (domain.empty()) {
        if (*separatorIndex == '/') {
          domain = url.subsequence(url.begin(), begin).stringRepresentation();
          url.eraseSequence(url.begin(), begin);
        } else if (*separatorIndex == '?') {
          domain = url.subsequence(url.begin(), begin).stringRepresentation();
          begin++;
          parameters = url.subsequence(begin, url.end()).stringRepresentation();
          query = "/";
          break;
        }
      } else {
        if (*separatorIndex == '?') {
          query = url.subsequence(url.begin(), begin).stringRepresentation();
          begin++;
          parameters = url.subsequence(begin, url.end()).stringRepresentation();
          break;
        }
      }
    }

    begin++;
  }

  if (!url.empty()) {
    if (domain.empty()) {
      domain = url.stringRepresentation();
    } else {
      query = url.stringRepresentation();
    }
  }

  if (query.empty())
    query = "/";
}

bool URL::compareDomains(const std::string& lhs, const std::string& rhs) {
  std::string lhsCopy = lhs, rhsCopy = rhs;

  if (lhsCopy.find(wwwPrefix) == 0)
    lhsCopy.erase(0, wwwPrefix.size());

  if (rhsCopy.find(wwwPrefix) == 0)
    rhsCopy.erase(0, wwwPrefix.size());

  return lhsCopy == rhsCopy;
}
