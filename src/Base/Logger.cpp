#include "Logger.hpp"

void Logger::logRequest(const Request& request, Level level) {
  switch (level) {
  case (Level::DEBUG):
  case (Level::INFO):
    std::cout << "Request:" << std::endl << request.createRequest() << std::endl;
    break;
  default: break;
  }
}

void Logger::logResponse(const Response& response, Level level) {
  std::cout << "Response:" << std::endl;
  switch (level) {
  case (Level::DEBUG):
    for (const auto& header: response.headers)
      std::cout << header.description() << std::endl;

    
    break;
  case (Level::INFO):
    break;
  case (Level::WARNING):
    break;
  }
}
