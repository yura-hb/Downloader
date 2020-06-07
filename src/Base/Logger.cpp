#include "Logger.hpp"

void Logger::logRequest(const Request& request) {
  std::cout << "Request:" << std::endl << request.createRequest();
}

void Logger::logResponse(const Response& response) {
  std::cout << "Response:" << std::endl;

  for (const auto& header: response.headers)
      std::cout << header.description() << std::endl;

  std::cout << std::endl;
}

void Logger::logError(const std::exception& response) {
  std::cerr << "Error:" << std::endl << response.what() << std::endl;
}
