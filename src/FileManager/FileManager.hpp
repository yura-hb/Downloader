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
#include "Models/Reference.hpp"

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
    void createPageFolder(const Reference& reference) const;
    /**
     * Description:
     *  Write file to the specific directory at the relative path in the folder with data.
     *  In case, if there are no folders with the specific path, creates them.
     *  Doesn't operate out of the folderName
     *
     * Params:
     *  @param[in] folderName: - Folder in the current directory
     *  @param[in] relativePath: - Relative path in the folder including filename
     *  @param[in] data: - data to save
     *
     * Exceptions:
     *  - In case if folder is not created throw exception
     *  - In case if any error occurs during write operation throws exceptions
     */
    void saveFile(const Reference& reference, const std::string& data) const;
    /**
     *  Clears the directory
     */
    // TODO: Ask user for permission
    void clearDirectory(const Reference& reference) const;
  private:
    // Disable copy constructor
    FileManager(FileManager &manager) {};
    FileManager& operator = (const FileManager& manager) { return *this; };
    /**
     *  Creates subdirectories, if they doesn't exist in the current directory
     */
    void createRelativePathDirectories(const Reference& reference) const;
    /**
     * List the files in the directory
     */
    std::vector<std::pair<std::string, uint8_t>> getFolderFiles(const Reference& reference) const;
    /**
     * Opens the specified directory.
     *
     * Throws:
     *  - In case, if the directory doesn't exist
     */
    void openDirectory(const Reference& reference, DIR *& dir) const;
};

#endif
