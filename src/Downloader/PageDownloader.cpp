#include "PageDownloader.hpp"

void PageDownloader::processOperations() {
  if (operationQueue.empty()) { return; }

  if (!operationQueue.front() -> perform()) {
    // TODO: - Log error
  }

  operationQueue.pop();
  processOperations();
}
