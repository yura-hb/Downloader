#include "FileManager.hpp"

std::string FileManager::createPageFolder(const std::string& name) const {
  int result;
  // TODO: - Replace cerr with the specified logger
  if ((result = mkdir(name.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) != 0)
    std::cerr << "Fail during creating directory" << std::endl;
  // Try to open directory with the name
  DIR *dir;
  openDirectory(name, dir);
  clearDirectory(name);
  closedir(dir);
  return name;
}

void FileManager::saveFile(const std::string& folderName, const std::string& relativePath, const std::string& data) const {
  std::string path = folderName + "/" + relativePath;

  createRelativePathDirectories(path);

  std::ofstream out(path, std::ios::out | std::ios::trunc);
  out << data;
}

std::vector<std::pair<std::string, uint8_t>> FileManager::getFolderFiles(const std::string& directory) const {
  DIR *dir;
  openDirectory(directory, dir);

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

void FileManager::createRelativePathDirectories(const std::string& path) const {
  std::list<std::string> list = splitPath(path);

  simplifyPath(list);

  // The base folder is already created and the last object of the path is string
  auto begin = list.begin();
  auto end = list.end();
  // The base folder is already created and the last object of the path is string
  begin++; end--;

  while (begin != end) {
    std::string path;
    // Create path
    for (auto it = list.begin(); it != begin; it++)
      path += *it + "/";
    // Load files from the folder
    std::vector<std::pair<std::string, uint8_t>> items = getFolderFiles(path);

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

std::list<std::string> FileManager::splitPath(const std::string& path) const {
  std::list<std::string> list;

  auto begin = path.begin();
  auto next = path.begin();
  while ((next = std::find(begin, path.end(), '/')) != path.end()) {
    list.push_back(std::string(begin, next));
    begin = next + 1;
  }
  if (begin == path.end())
    throw Exception("Path doesn't contain the filename");

  list.push_back(std::string(begin, path.end()));
  return list;
}

void FileManager::simplifyPath(std::list<std::string>& components) const {
  for (auto iter = components.begin(); iter != components.end(); iter++) {
    if (*iter == "" || *iter == ".")
      components.erase(iter--);

    if (*iter == "..") {
      components.erase(iter--);

      // In case, if the iter is at the relative root, don't perform any actions.
      if (iter == components.begin())
        continue;

      components.erase(iter--);
    }
  }
}

void FileManager::openDirectory(const std::string& directory, DIR *& dir) const {
  dir = opendir(directory.c_str());

  if (dir == nullptr)
    throw Exception("Directory doesn't exist");
}

void FileManager::clearDirectory(const std::string& directory) const {
  std::string command = "rm " + directory + "/*";
  system(command.c_str());
}
