#ifndef __ANALYZER_HPP__
#define __ANALYZER_HPP__

#include <iostream>
#include <vector>
#include <string>
#include "Models/Comment.hpp"
#include "Models/AbstractPattern.hpp"
#include "Models/Attribute.hpp"
#include "Models/Reference.hpp"

class Analyzer {
  public:
    Analyzer(std::vector<std::shared_ptr<AbstractPattern>> patterns): patterns(patterns) {}
    /**
     * Consumes the str and returns the founded references
     */
    virtual std::vector<Reference> loadReferences(const std::string& str);
    /**
     * Converts the references to files pathes on the local disk
     */
    virtual std::string convertToLocalReferences(std::string& str, std::vector<Reference> references);
  private:
    std::vector<std::shared_ptr<AbstractPattern>> patterns;
};

#endif
