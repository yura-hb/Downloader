#include <iostream>
#include "Base/ArgumentParser.hpp"

int main(int argc, char *argv[]) {
 // FileDownloader downloader;
 // downloader.download(RemoteReference("https://www.zdravionline.cz/imgs/articles/858-1_vychod_slunce_main.jpg"), LocalReference("test.jpg"));

  //PageMirror mirror;
  //mirror.mirror(RemoteReference("http://testing-ground.scraping.pro"));
  return ArgumentParser::handle(argc, argv);;
}
