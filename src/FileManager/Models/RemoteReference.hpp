#ifndef __REMOTE_REFERENCE__
#define __REMOTE_REFERENCE__

#include <iostream>
#include "Reference.hpp"
#include "../../Networking/URL.hpp"

struct RemoteReference: public Reference {
  public:
    RemoteReference(const std::string& link): Reference(Type::EXTERNAL_LINK), url(URL(link)) {}
    RemoteReference(const URL& url): Reference(Type::EXTERNAL_LINK), url(url) {}
    ~RemoteReference() = default;
    /**
     *  Discussion:
     *    Doesn't do anything, as not appliable on the links
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
     *    Add path to the url query
     *
     *  Input:
     *    - @param[in] - some path string
     *
     *  Output:
     *    - @param[out] - unique pointer on the new reference object
     */
    std::unique_ptr<Reference> addPath(const std::string& str) const override;
    /**
     *  Discussion:
     *    Validates, if the query points to the directory
     *
     *  Output:
     *    - @param[out] - boolean value validating, if the element is the reference
     */
    bool isDirectory() const override;
    /*
     *  Output:
     *    - @param[out] - false, as url can't be relative
     */
    bool isRelative() const override;
    /*
     *  Input:
     *    - @param[in] - domain of the link, discarded in case of the remote reference
     *  Output:
     *    - @param[out] - request url
     */
    URL requestUrl(const std::string& domain) const override;
    /*
     *  Output:
     *    - @param[out] - string representation of the url domain
     */
    std::string domain() const;
    /*
     *  Output:
     *    - @param[out] - string representation of the url query as a path
     */
    std::string getPath() const override;
  private:
    URL url;
};

#endif
