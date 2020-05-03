#ifndef __REFERENCE_HPP__
#define __REFERENCE_HPP__

#include <iostream>
#include <string>
#include "../../Networking/URL.hpp"
/**
 *  In HTML and CSS there are several types of references:
 *    1. External link - link to the external source, which contains HTTP and HTTPs
 *    2. Hyperlinks - relative links to the source files
 *
 *  External links are not important during mirroring process, as they contain information, which
 *  can be loaded by the browser during the view. Relative links should
 */
struct Reference {
  public:
    enum class Type {
      EXTERNAL_LINK,
      HYPER_LINK
    };

    Type type;
    const std::string& url;
    std::pair<uint32_t, uint32_t> index;
    /**
     * Create a reference
     *
     * @param[in] url - link from analyzer
     * @param[in] tuple of indexes in the original html
     */
    Reference(const std::string& url, std::pair<uint32_t, uint32_t> index): url(url), index(index) {
      type = URL(url).isValid() ?  Type::EXTERNAL_LINK : Type::HYPER_LINK;
    }

    friend std::ostream& operator<< (std::ostream& out, const Reference& ref) {
      out << ref.url << "Type: " << (int)ref.type << std::endl;
      return out;
    }
};

#endif
