#ifndef __LOCAL_REFERENCE_HPP__
#define __LOCAL_REFERENCE_HPP__

#include <iostream>
#include "Reference.hpp"
#include "../../Networking/URL.hpp"

struct LocalReference: public Reference {
  public:
    LocalReference() = default;
    LocalReference(const std::string& query, bool shouldSimplify = false): Reference(Type::HYPER_LINK), path(query) {
      if (shouldSimplify)
        simplify();
    }
    ~LocalReference() = default;
    /**
     *  @brief
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
     *  @brief
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
     *
     *  Throws:
     *    @throw - Exception, in case, if the file is the directory
     */
    std::unique_ptr<Reference> addFileExtension(const std::string& str) const override;
    /**
     *  @brief
     *    Validates, if the path is the directory
     *
     *  Output:
     *    - @param[out] - boolean value validating, if the element is the reference
     */
    bool isDirectory() const override;
    /**
     *  Output:
     *    - @param[out] - true, in case, if the reference is relative to some directory. (Starts with "/").
     */
    bool isRelative() const override;
    /**
     *  @brief
     *    Constructs url with the path as the query and the domain
     *
     *  Output:
     *    - @param[out] - true, in case, if the reference is relative to some directory. (Starts with "/").
     */
    URL requestUrl(const std::string& domain) const override;
    /**
     *  Output:
     *    - @param[out] - current path
     */
    std::string getPath() const override;
    /**
     *  Output:
     *    - @param[out] - returns the path of the current directory
     */
    std::string getDirectoryPath() const override;
    /**
     *  Output:
     *    - @param[out] - filename, in case if directory
     *
     *  Throws:
     *    In case, if current file is not directory
     */
    std::string filename() const override;
    /**
     *  Output:
     *    - @param[out] - path splitted on the / components
     */
    std::list<std::string> loadComponents() const;
    /**
     *  @brief
     *    Simplifies the path and removes all occurrences . // and ../ from the path.
     */
    void simplify();
  private:
    std::string path;
};

#endif
