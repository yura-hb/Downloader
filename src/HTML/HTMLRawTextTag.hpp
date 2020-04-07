#ifndef __HTML_RAW_TEXT_H__
#define __HTML_RAW_TEXT_H__

#include <iostream>
#include <string>
#include <set>
#include "HTMLElement.hpp"

/**
 * HTMLRawTextTag is the tag, which has no body, no end tag, but only attributes.
 */
struct HTMLRawTextTag: public HTMLElement {
  public:
    static const std::set<std::string> tags;

    HTMLRawTextTag(const std::string& elementName, const std::map<std::string, std::string>& attributes):
      HTMLElement(elementName, "", attributes) {};

    virtual HTMLElement::HTMLElementType getElementType() const override;
};

#endif
