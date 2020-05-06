#include <iostream>
#include "Downloader/PageDownloader.hpp"

int main() {

  PageDownloader downloader;
  downloader.mirror("www.oustranka.cz");

  return 0;
}
