#ifndef __ANALYZER_HPP__
#define __ANALYZER_HPP__

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <functional>

#include "Models/Comment.hpp"
#include "Models/AbstractPattern.hpp"
#include "Models/Attribute.hpp"
#include "Models/HTMLAttribute.hpp"
#include "Models/BeginEndAttribute.hpp"
#include "../FileManager/Models/LocalReference.hpp"

class Analyzer {
  public:
    Analyzer(const std::vector<std::shared_ptr<AbstractPattern>>& patterns): patterns(patterns) {}
    virtual ~Analyzer() = default;
    /**
     * @brief
     *   Reads bytes from the input file and checks for the url.
     *
     * Input:
     *   @param[in] str - reference to the local file
     *
     * Output:
     *   @param[out] - vector of the references
     */
    virtual std::vector<std::string> loadReferences(const LocalReference& str) const;
    /**
     * @brief
     *   Reads bytes from the input file and outputs them to the output file.
     *   For each reference, which was found, calls the input functor, which should return the new reference
     *
     * @param[in] file - input file path
     * @param[in] outputFile - output file path
     * @param[in] convertReferenceFunctor - converter function
     *
     * @return bool - in case, if the writing to the output stream succeeded returns true
     *
     * @throw Exception - in case, if the file or outputFile are directories.
     * @throw Exception - in case, if the file and outputFile have the same path
     */
    virtual bool overwriteReferences(const LocalReference& file,
                                     const LocalReference& outputFile,
                                     const std::function<Data<>(Data<>)>& convertReferenceFunctor) const;
  protected:
    std::vector<std::shared_ptr<AbstractPattern>> patterns;
};

#endif
