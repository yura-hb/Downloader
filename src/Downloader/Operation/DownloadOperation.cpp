#include "DownloadOperation.hpp"

/// TODO: - Implement logic for the downloading and processing errors
bool DownloadOperation::perform() {
  std::string result = "";

  client -> loadPage(url, result);

  return true;
}
