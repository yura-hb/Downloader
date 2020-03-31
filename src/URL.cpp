#include "URL.hpp"

URL::URL(const std::string &url) {
  parse(url);
}

bool URL::isValid() {
  return protocol != Protocol::undefined && !domain.empty() && domain.find(".") != domain.npos;
}

void URL::parse(const std::string &url) {
  try {
    std::regex regex(regexString);
    std::smatch match;
    std::cout << "start parsing" << std::endl;
    if (std::regex_search(url, match, regex) && match.size() == 6) {
      std:: cout << match.size() << std::endl;

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

      for (const auto &r: match) {
        std::cout << r << std::endl;
      }

      domain = match.str(2);
      query = match.str(4).empty() ? "/" : match.str(4);
      parameters = match.str(6);

      std::cout << domain << " " << query << " " << parameters << std::endl;
    }

      std:: cout << match.size() << std::endl;
  } catch (std::regex_error& error) {
    std::cerr << "URL: parse error" << error.code() << std::endl;
  }
}
