#ifndef __LOCAL_REFERENCE_HPP__
#define __LOCAL_REFERENCE_HPP__

#include <iostream>
#include "Reference.hpp"
#include "../../Networking/URL.hpp"

struct LocalReference: public Reference {
  public:
    LocalReference(const std::string& query, bool shouldSimplify = false): Reference(Type::HYPER_LINK), path(query) {
      if (shouldSimplify)
        simplify();
    }
    ~LocalReference() = default;
    /**
     *  Discussion:
     *    Add reference path to the current reference from the left
     *
     *  Input:
     *    - @param[in] - some path string
     *
     *  Output:
     *    - @param[out] - unique pointer on the new reference object
     */
    std::unique_ptr<Reference> addAbsoluteReference(const std::string& str) const override;
    /**
     *  Discussion:
     *    Add path to the reference query
     *
     *  Input:
     *    - @param[in] - some path string
     *
     *  Output:
     *    - @param[out] - unique pointer on the new reference object
     */
    std::unique_ptr<Reference> addPath(const std::string& str) const override;
    /**
     *  Input:
     *    - @param[in] - some file extension path
     *
     *  Output:
     *    - @param[out] - unique pointer on the new reference object
     */
    std::unique_ptr<Reference> addFileExtension(const std::string& str) const;
    /**
     *  Discussion:
     *    Validates, if the path is the directory
     *
     *  Output:
     *    - @param[out] - boolean value validating, if the element is the reference
     */
    bool isDirectory() const override;
    /*
     *  Output:
     *    - @param[out] - true, in case, if the reference is relative to some directory. (Starts with "/").
     */
    bool isRelative() const override;
    /*
     *  Discussion:
     *    Constructs url with the path as the query and the domain
     *
     *  Output:
     *    - @param[out] - true, in case, if the reference is relative to some directory. (Starts with "/").
     */
    URL requestUrl(const std::string& domain) const override;
    /*
     *  Output:
     *    - @param[out] - current path
     */
    std::string getPath() const;
    /*
     *  Output:
     *    - @param[out] - path splitted on the / components
     */
    std::list<std::string> loadComponents() const;
  private:
    std::string path;
    /*
     *  Discussion:
     *    Simplifies the path and removes all occurrences . // and ../ from the path.
     */
    void simplify();
};

#endif
