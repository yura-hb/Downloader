#include "HTTPParser.hpp"

const std::string Parser::separator = "\r\n\r\n";

const ResponseStatus Parser::parseStatus(const std::string& response) {
  std::stringstream splitStream(response);
  std::string line = "";

  if (!getline(splitStream, line))
    throw Exception("Incorrect response");

  return ResponseStatus(line);
}

const std::vector<Header> Parser::parse(const std::string& response) {
  std::vector<Header> components  = {};

  std::stringstream splitStream(getHeader(response));
  std::string line = "";

  while (getline(splitStream, line)) {
    try {
     // std::cout << line << std::endl << std::endl;
      Header header(line);
      components.push_back(header);
    } catch (const std::exception& exc) {
     // std::cerr << "Parser: error " << exc.what() << "[" << line << "]" << std::endl;
    } catch (...) {
      continue;
    }
  }

  return components;
}

const std::string Parser::body(const std::string& response) {
  return std::string(response.begin() + response.find(separator) + separator.size(), response.end());
}

const std::string Parser::getHeader(const std::string& response) {
  auto index = response.find(separator);
  return std::string(response.begin(), response.begin() + index);
}
