#ifndef __REFERENCE_CONVERTER__
#define __REFERENCE_CONVERTER__

#include <iostream>
#include <memory>
#include "RemoteReference.hpp"
#include "LocalReference.hpp"
#include "../../Networking/URL.hpp"

class ReferenceConverter {
  public:
    static std::shared_ptr<Reference> convert(const std::string& str) {
      URL url(str);

      if (url.isValid())
        return std::make_shared<RemoteReference>(url);
      else
        return std::make_shared<LocalReference>(str, true);
    }

    static URL makeRequest(const std::string& domain, const std::shared_ptr<Reference>& ref) {
      return ref -> requestUrl(domain);
    }
};

#endif
