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

#include "Models/LocalReference.hpp"
#include "../Base/Exception.hpp"
#include "../Base/Data.hpp"
#include "../Base/Logger.hpp"

class FileManager {
  public:
    FileManager() = default;
    /**
     * @brief
     *   Creates folder at the current directory with the specific name and returns the full path to the folder
     *
     * Input:
     *   - @param[in] - local reference to the folder
     */
    void createFolder(const LocalReference& reference) const;
    /**
     * @brief
     *  Write file to the specific directory at the relative path in the folder with data.
     *  In case, if there are no folders with the specific path, creates them.
     *  Doesn't operate out of the folderName
     *
     * Input:
     *   - @param[in] reference: - Reference to the specific file
     *   - @param[in] data: - data to save
     *
     * Throws:
     *  - In case if folder is not created throw exception
     *  - In case if any error occurs during write operation throws exceptions
     */
    void saveFile(const LocalReference& reference, const Data<>& data, const Data<>::iterator& startPosition) const;
    /**
     *  @brief
     *    Clears the directory by calling rm -r * on some path
     *
     *  Input:
     *    - @param[in] - local reference to the folder
     */
    void clearDirectory(const LocalReference& reference) const;
    /**
     * @brief
     *   Calls mv on the specific files
     *
     * @param[in] oldName - old file name
     * @param[in] newName - new file name
     *
     * @return int - the result of the command
     */
    int rename(const std::string& oldName, const std::string& newName);
  private:
    // Disable copy constructor
    FileManager(FileManager &manager) {};
    FileManager& operator = (const FileManager& manager) { return *this; };
    /**
     *  @brief
     *    Creates subdirectories, if they doesn't exist in the current directory
     *
     *  Input:
     *    - @param[in] - reference to all the directories
     *
     */
    void createRelativePathDirectories(const LocalReference& reference) const;
    /**
     * List the files in the directory
     */
    std::vector<std::pair<std::string, uint8_t>> getFolderFiles(const LocalReference& reference) const;
    /**
     * Opens the specified directory.
     *
     * Throws:
     *  - In case, if the directory doesn't exist
     */
    void openDirectory(const LocalReference& reference, DIR *& dir) const;
};

#endif
