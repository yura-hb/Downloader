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
    std::string path;

    Reference() : type(Type::HYPER_LINK), path("/") {}
    /**
     * Create a reference, depending on the type of the reference. Then simplifies it
     *
     * @param[in] url - link from analyzer
     * @param[in] tuple of indexes in the original html
     */
    Reference(const std::string& path, bool shouldSimplify = false):
      type(URL(path).isValid() ? Type::EXTERNAL_LINK : Type::HYPER_LINK),
      path(path) {
      if (shouldSimplify)
        simplify();
    }
    Reference(const std::string& path, Type type):
      type(type), path(path) {}
    ~Reference() = default;
    /**
     * Validates, if the item is directory
     */
    bool isDirectory() const;
    /**
     * Validates, if the directory is relative
     */
    bool isRelative() const;
    /**
     * Add reference from the left.
     *
     * Throws:
     *   - In case if the called on the External link
     */
    Reference addAbsoleteReference(const std::string& str) const;
    /**
     * Add reference from the right.
     *
     * Throws:
     *   - In case if the called on the External link
     */
    Reference addPath(const std::string& str) const;
    /**
     * Split string on the list of subpathes
     */
    std::list<std::string> loadComponents() const;

    friend std::ostream& operator<< (std::ostream& out, const Reference& ref);
  private:
    void simplify();
};

#endif
