#include <iostream>
#include "FileManager/FileManager.hpp"
#include "SyntaxAnalyzer/HTMLAnalyzer.hpp"

int main() {
  FileManager manager;

  std::string name = "Test, st";

  std::ifstream stream("index.html");

  std::string str((std::istreambuf_iterator<char>(stream)),
                  std::istreambuf_iterator<char>());

  //std::cout << str;

  HTMLAnalyzer a;

  a.loadReferences(str);

  try {
   // manager.createPageFolder(name);
   // manager.saveFile(name, "test/test/a/b/c/test.txt", "bla-bla-bla-bla-bla");
   // manager.clearDirectory(name);
  } catch (const FileManager::Exception& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
