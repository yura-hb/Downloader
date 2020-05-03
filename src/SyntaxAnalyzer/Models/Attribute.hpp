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
    Attribute(std::string begin, std::string end, std::string separator = "="): AbstractPattern(begin, end, separator) {}

    bool consume(const Range& range, const EmitFunction& func) const override;
};

#endif
