#ifndef __LOCAL_REFERENCE_HPP__
#define __LOCAL_REFERENCE_HPP__

#include <iostream>
#include "Reference.hpp"

struct LocalReference: public Reference {
  public:
    LocalReference(const std::string& query, bool shouldSimplify = false): Reference(Type::HYPER_LINK), path(query) {
      if (shouldSimplify)
        simplify();
    }
    ~LocalReference() = default;

    std::unique_ptr<Reference> addAbsoleteReference(const std::string& str) const override;
    std::unique_ptr<Reference> addPath(const std::string& str) const override;

    bool isDirectory() const override;
    bool isRelative() const override;

    std::string requestUrl(const std::string& domain) const override;
    std::string getPath() const;

    std::list<std::string> loadComponents() const;
  private:
    std::string path;

    void simplify();
};

#endif
