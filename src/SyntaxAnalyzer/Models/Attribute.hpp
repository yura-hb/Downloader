#ifndef __ATTRIBUTE_HPP__
#define __ATTRIBUTE_HPP__

#include <iostream>
#include "AbstractPattern.hpp"

struct Attribute: public AbstractPattern {
  public:
    Attribute(const std::string& begin, const std::string& separator, const std::string& end): AbstractPattern(begin, separator, end) {}

    bool consume(const Input& input, const EmitFunction& func) const;

  private:
    static std::vector<char> whitespaces;
    /**
     *  Input:
     *    - @param[in] input - pair of input stream and buffer.
     *
     *  Output:
     *    - @param[out] - boolean value, indicating if the read succeeds.
     *
     */
    bool readUntilSeparator(const Input& input) const;
    /**
     *  Input:
     *    - @param[in] input - pair of input stream and buffer.
     *    - @param[in] isInitial - flag, indicating, if the read isInitial. In case, if true, checks,
     *                 if read bytes are only whitespace characters and reads until single or double quote.
     *    - @param[in] quote - quote string. (Affects on the reading process, only in case !isInitial).
     *
     *  Output:
     *    - @param[out] quote - in case, if isInitial, sets the quote founded.
     *    - @param[out] - boolean value, indicating if the read succeeds.
     *
     */
    bool readUntilQuote(const Input& input, bool isInitial, std::string& quote) const;
};

#endif
