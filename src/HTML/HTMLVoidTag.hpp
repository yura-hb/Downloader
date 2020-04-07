#ifndef __HTML_VOID_H__
#define __HTML_VOID_H__

#include <iostream>
#include <string>
#include <set>
#include "HTMLElement.hpp"

/**
 * HTMLVoidTag is the tag, which has no body, no end tag, but only attributes.
 */
struct HTMLVoidTag: public HTMLElement {
  public:
    static const std::set<std::string> tags;

    HTMLVoidTag(const std::string& elementName, const std::map<std::string, std::string>& attributes):
      HTMLElement(elementName, "", attributes) {};

    virtual HTMLElement::HTMLElementType getElementType() const override;
};

#endif
