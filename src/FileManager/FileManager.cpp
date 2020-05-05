#include "FileManager.hpp"

void FileManager::createPageFolder(const Reference& reference) const {
  int result;
  // TODO: - Replace cerr with the specified logger
  if ((result = mkdir(reference.path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) != 0)
    std::cerr << "Fail during creating directory" << std::endl;
  // Try to open directory with the name
  DIR *dir;
  openDirectory(reference, dir);
  closedir(dir);
}

void FileManager::saveFile(const Reference& reference, const std::string& data) const {
  createRelativePathDirectories(reference.path);
  std::ofstream out(reference.path, std::ios::out | std::ios::trunc);
  out << data;
}

std::vector<std::pair<std::string, uint8_t>> FileManager::getFolderFiles(const Reference& reference) const {
  DIR *dir;
  openDirectory(reference, dir);

  std::vector<std::pair<std::string, uint8_t>> result;
  struct dirent* entry;

  while ((entry = readdir(dir)))
    result.push_back(std::pair<std::string, uint8_t>(
      std::string(entry ->d_name),
      entry -> d_type
    ));

  closedir(dir);
  return result;
}

void FileManager::createRelativePathDirectories(const Reference& reference) const {
  std::list<std::string> list = reference.loadComponents();
  // The base folder is already created and the last object of the path is string
  auto begin = list.begin();
  auto end = list.end();
  begin++; end--;

  while (begin != end) {
    std::string path;
    // Create path
    for (auto it = list.begin(); it != begin; it++)
      path += *it + "/";

    // Load files from the folder
    std::vector<std::pair<std::string, uint8_t>> items = getFolderFiles(Reference(path));

    bool didFoundFile = false;

    for (const auto& item: items) {
      auto comparisonResult = item.first == *begin;

      if (comparisonResult && item.second == DT_DIR) {
        didFoundFile = true;
        break;
      } else if (comparisonResult) {
        throw Exception("Can't create folder, as file with the directory name exists");
      }
    }

    if (!didFoundFile)
      createPageFolder(path + *begin);

    begin++;
  }
}

void FileManager::openDirectory(const Reference& reference, DIR *& dir) const {
  dir = opendir(reference.path.c_str());

  if (dir == nullptr)
    throw Exception("Directory doesn't exist");
}

void FileManager::clearDirectory(const Reference& reference) const {
  std::string command = "rm -r '" + reference.path + "'/*";
  std::cout << command;
  system(command.c_str());
}
