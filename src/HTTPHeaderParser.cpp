#include "HTTPHeaderParser.hpp"

const std::vector<Header> HeaderParser::parse(const std::string headers) {
  std::vector<Header> components  = {};

  std::stringstream splitStream(headers);
  std::string line = "";

  while (getline(splitStream, line, '\n')) {
    try {
      Header headers(line);
    } catch (const std::exception& exc) {
      std::cerr << "Parser: error" << exc.what() << " " << line << std::endl;
    }
  }

  return components;
}
