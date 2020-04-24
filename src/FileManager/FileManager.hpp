#ifndef __FILE_MANAGER__
#define __FILE_MANAGER__

#include <iostream>
#include <sys/stat.h>
#include <string>
#include <exception>

class FileManager {
  public:
    // Constructor
    FileManager() = default;
    /**
     * Creates folder at the current directory with the specific name
     */
    void createPageFolder(const std::string& name);
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
     *
     */
    void saveFile(const std::string& folderName, const std::string& relativePath, const std::string& data);
  private:
    // Disable copy constructor
    FileManager(FileManager &manager) {};
    FileManager& operator = (const FileManager& manager) { return *this; };
};

#endif
