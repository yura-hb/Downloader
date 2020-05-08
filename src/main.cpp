#include <iostream>
#include "Downloader/Downloader.hpp"

int main() {
  Downloader downloader;
  downloader.download(RemoteReference("https://i.stack.imgur.com/BNjyq.png"), LocalReference("test.txt"));

  return 0;
}

