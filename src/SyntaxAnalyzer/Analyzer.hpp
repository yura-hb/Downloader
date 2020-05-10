#ifndef __ANALYZER_HPP__
#define __ANALYZER_HPP__

#include <iostream>
#include <vector>
#include <string>
#include "Models/Comment.hpp"
#include "Models/AbstractPattern.hpp"
#include "Models/Attribute.hpp"
#include "../FileManager/Models/LocalReference.hpp"

class Analyzer {
  public:
    Analyzer(const std::vector<std::shared_ptr<AbstractPattern>>& patterns): patterns(patterns) {}
    virtual ~Analyzer() = default;
    /**
     * Discussion:
     *   Reads bytes from the input file and checks for the url.
     *
     * Input:
     *   @param[in] str - reference to the local file
     *
     * Output:
     *   @param[out] - vector of the references
     */
    virtual std::vector<std::string> loadReferences(const LocalReference& str) const;
  protected:
    std::vector<std::shared_ptr<AbstractPattern>> patterns;
};

#endif
