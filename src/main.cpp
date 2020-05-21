#include <iostream>

#include "Downloader/PageMirror.hpp"
#include "Downloader/Helpers/DownloadFileTree.hpp"

int main() {
 // FileDownloader downloader;
 // downloader.download(RemoteReference("https://www.zdravionline.cz/imgs/articles/858-1_vychod_slunce_main.jpg"), LocalReference("test.jpg"));

  PageMirror mirror;
  mirror.mirror(RemoteReference("www.oustranka.cz"));


  return 0;
}
