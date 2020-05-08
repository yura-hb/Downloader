#include <iostream>
#include "Downloader/PageDownloader.hpp"

int main() {
  PageDownloader downloader;
  downloader.download("https://i.stack.imgur.com/BNjyq.png");

  return 0;
}
