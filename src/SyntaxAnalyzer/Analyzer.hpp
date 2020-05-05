#ifndef __ANALYZER_HPP__
#define __ANALYZER_HPP__

#include <iostream>
#include <vector>
#include <string>
#include "Models/Comment.hpp"
#include "Models/AbstractPattern.hpp"
#include "Models/Attribute.hpp"
#include "../FileManager/Models/Reference.hpp"

class Analyzer {
  public:
    Analyzer(const std::vector<std::shared_ptr<AbstractPattern>>& patterns): patterns(patterns) {}
    virtual ~Analyzer() = default;
    /**
     * Consumes the str and returns the founded references
     */
    virtual std::vector<Reference> loadReferences(const std::string& str) const;
    /**
     * Converts the references to files pathes on the local disk
     */
    virtual std::string convertToLocalReferences(std::string& str, const std::vector<Reference>& references) const;
  protected:
    std::vector<std::shared_ptr<AbstractPattern>> patterns;
};

#endif
