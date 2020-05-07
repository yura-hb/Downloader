#include <iostream>
#include "Downloader/PageDownloader.hpp"

int main() {

  PageDownloader downloader;
  downloader.mirror("https://jigsaw.w3.org/HTTP/ChunkedScript");

  return 0;
}
