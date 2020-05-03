#include <iostream>
#include "FileManager/FileManager.hpp"

int main() {
  FileManager manager;

  std::string name = "Test, st";
  try {
    manager.createPageFolder(name);
    manager.saveFile(name, "test/test/a/b/c/test.txt", "bla-bla-bla-bla-bla");
  } catch (const FileManager::Exception& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
