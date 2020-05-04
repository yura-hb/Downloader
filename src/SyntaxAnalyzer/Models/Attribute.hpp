#ifndef __ATTRIBUTE_HPP__
#define __ATTRIBUTE_HPP__

#include <iostream>
#include "AbstractPattern.hpp"

/**
 * HTML or CSS attribute
 *
 * For HTML attribute looks for the next pattern:
 *   attributeName = attributeValue,
 * where attribute value can be in single or double quotes.
 *
 * For CSS look for the next clause
 *   url("value"), where value can have single or double quotes
 */
struct Attribute: public AbstractPattern {
  public:
    Attribute(const std::string& begin, const std::string& separator, const std::string& end): AbstractPattern(begin, separator, end) {}

    bool consume(const Range& range, const EmitFunction& func) const override;
};

#endif
