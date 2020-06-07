#include "FileManager.hpp"

void FileManager::createFolder(const LocalReference& reference) const {
  int result;

  if ((result = mkdir(reference.getPath().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) != 0)
    Logger::logError(Exception("Fail during creating directory"));

  // In case of error, try to open directory with the name
  if (result) {
    DIR *dir;
    openDirectory(reference, dir);
    closedir(dir);
  }
}

void FileManager::saveFile(const LocalReference& reference, const Data<>& data, const Data<>::iterator& startPosition) const {
  createRelativePathDirectories(reference.getPath());
  std::ofstream out(reference.getPath(), std::ios::out | std::ios::trunc);

  if (out.bad())
    throw Exception("Can't open file");

  data.write(out, startPosition, data.end());

  if (out.bad())
    throw Exception("File write failed");
}

std::vector<std::pair<std::string, uint8_t>> FileManager::getFolderFiles(const LocalReference& reference) const {
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

void FileManager::createRelativePathDirectories(const LocalReference& reference) const {
  std::list<std::string> list = reference.loadComponents();

  auto begin = list.begin();
  auto end = list.end();
  end--;

  while (begin != end) {
    std::string path = "";

    // Create path
    for (auto it = list.begin(); it != begin; it++)
      path += *it + "/";

    // Load files from the folder
    std::vector<std::pair<std::string, uint8_t>> items = getFolderFiles(LocalReference(path));
    bool didFoundFile = false;

    for (const auto& item: items) {
      auto comparisonResult = item.first == *begin;

      if (comparisonResult && item.second == DT_DIR) {
        didFoundFile = true;
        break;
      }
    }

    if (!didFoundFile)
      createFolder(path + *begin);

    begin++;
  }
}

int FileManager::rename(const std::string& oldName, const std::string& newName) {
  std::ostringstream s;
  s << "mv" << " '" << oldName << "' '" << newName << "'";
  return system(s.str().c_str());
}

int FileManager::remove(const std::string& name) {
  std::ostringstream s;
  s << "rm " << "'" << name << "'";
  return system(s.str().c_str());
}

void FileManager::openDirectory(const LocalReference& reference, DIR *& dir) const {
  std::string path = reference.getPath();
  // In case of empty directory, check current
  path = path + (path == "" ? "." : "");

  dir = opendir(path.c_str());

  if (dir == nullptr)
    throw Exception("Directory doesn't exist");
}

void FileManager::clearDirectory(const LocalReference& reference) const {
  std::string command = "rm -r '" + reference.getPath() + "'/*";
  system(command.c_str());
}
