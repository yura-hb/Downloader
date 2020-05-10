#include <iostream>

#include "Downloader/PageMirror.hpp"
#include "Downloader/Helpers/DownloadFileTree.hpp"

int main() {
 // FileDownloader downloader;
 // downloader.download(RemoteReference("http://www.oustranka.cz"), LocalReference("test.txt"));

  PageMirror mirror;
  mirror.mirror(RemoteReference("http://www.oustranka.cz"));


  return 0;
}
