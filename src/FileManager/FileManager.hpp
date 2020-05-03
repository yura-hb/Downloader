#ifndef __FILE_MANAGER__
#define __FILE_MANAGER__

#include <iostream>
#include <sys/stat.h>
#include <exception>
#include <string>
#include <fstream>
#include <dirent.h>
#include <vector>
#include <list>
#include <algorithm>

// TODO: - Return folder name
class FileManager {
  public:
    // Nested
    class Exception {
      public:
        Exception(const std::string& object): object(object) {}

        const char * what() const throw() {
          return object.c_str();
        }
      private:
        const std::string object;
    };
    // Constructor
    FileManager() = default;
    /**
     * Creates folder at the current directory with the specific name and returns the full path to the folder
     */
    std::string createPageFolder(const std::string& name) const;
    /**
     * Description:
     *  Write file to the specific directory at the relative path in the folder with data.
     *
     * Params:
     *  @param[in]: - Folder in the current directory
     *  @param[in]: - Relative path in the folder including filename
     *  @param[in]: - data to save
     *
     * Exceptions:
     *  - In case if folder is not created throw exception
     *  - In case if any error occurs during write operation throws exceptions
     */
    void saveFile(const std::string& folderName, const std::string& relativePath, const std::string& data) const;
  private:
    // Disable copy constructor
    FileManager(FileManager &manager) {};
    FileManager& operator = (const FileManager& manager) { return *this; };
    /**
     * Creates subdirectories, if they doesn't exist in the current directory.
     *
     * Supports '.' and '..' path components.
     */
    void createRelativePathDirectories(const std::string& path) const;
    /**
     * List the files in the directory
     */
    std::vector<std::pair<std::string, uint8_t>> getFolderFiles(const std::string& directory) const;
    /**
     *  Split the path by the '/'
     */
    std::list<std::string> splitPath(const std::string& path) const;
    /**
     *  Simplify the path by removing extra '/' and '.' and applying actions on the '..'
     */
    void simplifyPath(std::list<std::string>& components) const;
    /**
     * Opens the specified directory
     */
    void openDirectory(const std::string& directory, DIR *& dir) const;
    /**
     * Clears the directory
     */
    void clearDirectory(const std::string& directory) const;
};

#endif
