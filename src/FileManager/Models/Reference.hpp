#ifndef __REFERENCE_HPP__
#define __REFERENCE_HPP__

#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <list>
#include <functional>
#include "../../Networking/URL.hpp"
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
    enum class Type {
      EXTERNAL_LINK,
      HYPER_LINK
    };

    Type type;
    /**
     * Create a reference, depending on the type of the reference. Then simplifies it
     *
     * @param[in] url - link from analyzer
     * @param[in] tuple of indexes in the original html
     */
    Reference(const std::string& path):
      type(URL(path).isValid() ?  Type::EXTERNAL_LINK : Type::HYPER_LINK),
      path(path) {
      simplify();
    }
    ~Reference();
    /**
     * Validates, if the item is directory
     */
    bool isDirectory();
    /**
     * Validates, if the directory is relative
     */
    bool isRelative();
    /**
     * Add reference from the left.
     *
     * Throws:
     *   - In case if the called on the External link
     */
    Reference addAbsoleteReference(const std::string& str);
    /**
     * Add reference from the right.
     *
     * Throws:
     *   - In case if the called on the External link
     */
    Reference addPath(const std::string& str);

    friend std::ostream& operator<< (std::ostream& out, const Reference& ref);
  protected:
    std::string path;
  private:
    std::list<std::string> loadComponents();
    void simplify();
};

#endif
