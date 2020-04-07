#include "HTTPParser.hpp"

const ResponseStatus Parser::parseStatus(const std::string& response) {
  std::stringstream splitStream(response);
  std::string line = "";

  if (!getline(splitStream, line))
    throw "Incorrect response";

  return ResponseStatus(line);
}

const std::vector<Header> Parser::parse(const std::string& response) {
  std::vector<Header> components  = {};

  std::stringstream splitStream(getHeader(response));
  std::string line = "";

  std::cout << getHeader(response) << std::endl << std::endl;
  while (getline(splitStream, line)) {
    try {
      Header header(line);
      components.push_back(header);
    } catch (const std::exception& exc) {
      std::cerr << "Parser: error" << exc.what() << " " << line << std::endl;
    } catch (...) {
      continue;
    }
  }

  return components;
}

const std::string Parser::getHeader(const std::string& response) {
  auto index = response.find("\r\n\r\n");
  return std::string(response.begin(), response.begin() + index);
}
