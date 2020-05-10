#include "URL.hpp"

const std::string URL::regexString = "^(http\\:\\/\\/|https\\:\\/\\/|ftp\\:\\/\\/)?([a-z0-9\\-\\.]+)(\\:[0-9]+)?(\\/[^?]+)?[\\?]?(.*)?$";

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
      break;
    case Protocol::undefined:
      result += "";
      break;
  }

  result += port +  domain + query;

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

void URL::parse(const std::string &url) {
  try {
    std::regex regex(URL::regexString);
    std::smatch match;
    if (std::regex_search(url, match, regex) && match.size() == 6) {

      std::string protocolMatch = match.str(1);

      if (protocolMatch == "http://") {
        protocol = Protocol::http;
      } else if (protocolMatch == "https://") {
        protocol = Protocol::https;
      } else if (protocolMatch == "ftp://") {
        protocol = Protocol::ftp;
      } else if (protocolMatch == "") {
        protocol = Protocol::http;
      }

      domain = match.str(2);
      port = match.str(3);
      query = match.str(4).empty() ? "/" : match.str(4);
      parameters = match.str(5);
    }
  } catch (std::regex_error& error) {
    std::cerr << "URL: parse error" << error.code() << std::endl;
  }
}
