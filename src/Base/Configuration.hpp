#ifndef __CONFIGURATION_HPP__
#define __CONFIGURATION_HPP__

#include <iostream>

class Configuration {
  public:
    static Configuration shared;
    /**
     * @brief
     *   In case, if is true, the downloaded html and css file references are overwritten using local references.
     */
    bool overrideReferences = false;
    /**
     * @brief
     *   In case, if is true, the downloaded html and css original files are not removed
     */
    bool removedOriginFiles = true;
    /**
     * @brief
     *   HTML files downloaded from the site doesn't have .html file extension, by enabling this flag will fix them
     */
    bool fixHtmlPathes = false;
};

#endif
