#ifndef __ARGUMENT_PARSER__
#define __ARGUMENT_PARSER__

#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <cstring>
#include <exception>

#include "../FileManager/FileManager.hpp"
#include "../Downloader/PageMirror.hpp"
#include "Configuration.hpp"

class ArgumentParser {
  public:
    /**
     * @brief
     *
     * @param[in] argc - arguments count
     * @param[in] argv - arguments values
     */
    static int handle(const int argc, char * argv[]);

  private:
    /**
     * @brief
     *   Notify user about error.
     */
    static void notifyError();
    /**
     * @brief
     *   Shows user help message.
     *
     */
    static void showUserHelpMessage();
    /**
     * @brief
     *   Processes the argument by filling map of the arguments. In case, of error show error message.
     *
     * @param[in] argc - arguments count
     * @param[in] argv - arguments
     * @param[in] arguments - empty map
     * @param[in] link - empty link
     * @param[in] depth - depth
     *
     * @param[out] arguments - filled map with the flags
     * @param[out] link - link
     * @param[out] depth - depth
     */
    static int processArguments(int argc, char *argv[], std::map<std::string, bool>& arguments, std::string& link, size_t& depth);
    /**
     * @brief
     *   Reacts on the arguments from the input
     *
     * @param[in] arguments - filled arguments map
     * @param[in] link - link to the element to mirror or download
     * @param[in] depth - maximal download depth
     */
    static int handleArguments(const std::map<std::string, bool>& arguments, const std::string& link, const size_t& depth);
};

#endif
