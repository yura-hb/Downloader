#ifndef __BEGIN_END_ATTRIBUTE_HPP__
#define __BEGIN_END_ATTRIBUTE_HPP__

#include <iostream>
#include "AbstractPattern.hpp"

/**
 * @brief
 *   The attribute model, which implements case, when we need to read until begin end.
 *   This is useful in the parsing css, where such cases are possible.
 */
struct BeginEndAttribute: public AbstractPattern {
  public:
    BeginEndAttribute(const std::string& begin,
                      const std::string& separator,
                      const std::string& end,
                      const bool& trimQuotes = false): AbstractPattern(begin, separator, end), trimQuotes(trimQuotes) {}

    bool consume(const Input& input, const EmitFunction& func) const override;

  private:
    const bool trimQuotes;
};

#endif
