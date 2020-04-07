#ifndef __HTML_TEMPLATE_H__
#define __HTML_TEMPLATE_H__

#include <iostream>
#include <string>
#include <set>
#include "HTMLElement.hpp"

/**
 * HTMLTemplateTag is the tag, which has no body, no end tag, but only attributes.
 */
struct HTMLTemplateTag: public HTMLElement {
  public:
    static const std::set<std::string> tags;

    HTMLTemplateTag(const std::string& elementName, const std::map<std::string, std::string>& attributes):
      HTMLElement(elementName, "", attributes) {};

    virtual HTMLElement::HTMLElementType getElementType() const override;
};

#endif
