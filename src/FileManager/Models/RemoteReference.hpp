#ifndef __REMOTE_REFERENCE__
#define __REMOTE_REFERENCE__

#include <iostream>
#include "Reference.hpp"

struct RemoteReference: public Reference {
  public:
    RemoteReference(const std::string& link): Reference(Type::EXTERNAL_LINK), url(URL(link)) {}
    RemoteReference(const URL& url): Reference(Type::EXTERNAL_LINK), url(url) {}
    ~RemoteReference() = default;

    std::unique_ptr<Reference> addAbsoleteReference(const std::string& str) const override;
    std::unique_ptr<Reference> addPath(const std::string& str) const override;

    bool isDirectory() const override;
    bool isRelative() const override;

    std::string requestUrl(const std::string& domain) const override;
    std::string domain();
    std::string query();
  private:
    URL url;
};

#endif
