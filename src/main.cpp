#include <iostream>
#include "FileManager/FileManager.hpp"
#include "SyntaxAnalyzer/HTMLAnalyzer.hpp"
#include "FileManager/Models/Reference.hpp"
#include "Downloader/PageDownloader.hpp"

int main() {

  PageDownloader downloader;
  downloader.mirror("www.oustranka.cz");


/*

  std::string name = "Test, st";

  std::ifstream stream("index.html");

  std::string str((std::istreambuf_iterator<char>(stream)),
                  std::istreambuf_iterator<char>());

  HTMLAnalyzer a;

  a.loadReferences(str);

  Reference ref("../../../..//v/a.txt", true);
  std::cout << ref;

  try {

    FileManager manager;

    manager.createPageFolder(Reference("test"));
    std::cout << Reference("test/test/test/a.txt") << std::endl;
    manager.saveFile(Reference("test/test/test/a.txt"), "bla-bla-bla");
   // manager.createPageFolder(name);
   // manager.saveFile(name, "test/test/a/b/c/test.txt", "bla-bla-bla-bla-bla");
   // manager.clearDirectory(name);
  } catch (const FileManager::Exception& e) {
    std::cout << e.what() << std::endl;
  }*/
  return 0;
}
