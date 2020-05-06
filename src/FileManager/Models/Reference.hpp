#ifndef __REFERENCE_HPP__
#define __REFERENCE_HPP__

#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <list>
#include <functional>
#include "../../Networking/URL.hpp"
#include "../../Templates/Exception.hpp"
/**
 *  In HTML and CSS there are several types of references:
 *    1. External link - link to the external source, which contains HTTP and HTTPs
 *    2. Hyperlinks - relative links to the source files
 *
 *  External links are not important during mirroring process, as they contain information, which
 *  can be loaded by the browser during the view.
 *  Links should separated on the root directory link and current directory links
 */
struct Reference {
  public:
    enum class Type {
      EXTERNAL_LINK = 0,
      HYPER_LINK
    };

    Type type;

    Reference() = default;
    Reference(const Type type): type(type) {}
    virtual ~Reference() = default;
    /**
     * Validates, if the item is directory
     */
    virtual bool isDirectory() const = 0;
    /**
     * Validates, if the directory is relative
     */
    virtual bool isRelative() const = 0;
    /**
     * Add reference from the left.
     */
    virtual std::unique_ptr<Reference> addAbsoleteReference(const std::string& str) const = 0;
    /**
     * Add reference from the right.
     */
    virtual std::unique_ptr<Reference> addPath(const std::string& str) const = 0;
    /**
     * Create request URL
     */
    virtual std::string requestUrl(const std::string& domain) const = 0;
  protected:
    std::string path;
};

#endif
