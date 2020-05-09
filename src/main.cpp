#include <iostream>
#include "Downloader/FileDownloader.hpp"

int main() {
  FileDownloader downloader;
  downloader.download(RemoteReference("http://www.oustranka.cz"), LocalReference("test.txt"));
  return 0;
}
