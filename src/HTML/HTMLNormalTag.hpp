#ifndef __HTML_NORMAL_H__
#define __HTML_NORMAL_H__

#include <iostream>
#include <string>
#include "HTMLElement.hpp"

/**
 * HTMLNormalTag is the tag, which has no body, no end tag, but only attributes.
 */
struct HTMLNormalTag: public HTMLElement {
  public:
    static const std::vector<std::string> tags;

    HTMLNormalTag(const std::string& elementName, const std::map<std::string, std::string>& attributes):
      HTMLElement(elementName, "", attributes) {};

    virtual HTMLElement::HTMLElementType getElementType() const override;
};

#endif
