#ifndef __HTML_ATTRIBUTE_HPP__
#define __HTML_ATTRIBUTE_HPP__

#include "Attribute.hpp"
#include "string"

/**
 * @brief
 *   Wrapper around the HTMLAttribute, which filters out javascript and tag references
 */
class HTMLAttribute: public Attribute {
  public:
    HTMLAttribute(const std::string& begin, const std::string& separator, const std::string& end): Attribute(begin, separator, end) {}

    bool consume(const Input& input, const EmitFunction& func) const override;

  private:
    static const std::string javascriptPrefix;
    static const std::string tag;
};

#endif
