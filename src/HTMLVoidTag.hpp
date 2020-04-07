#ifndef __HTML_VOID_H__
#define __HTML_VOID_H__

#include <iostream>
#include "HTMLElement.hpp"

struct HTMLVoidTag: public HTMLElement {
  public:
    const std::string getTagName() override;
    const HTMLElement::HTMLElementType getType() override;
    const std::string getData() override;
    const std::map<std::string, std::string> getAttributes() const override;
    const std::vector<HTMLElement> getChildren() const override;
    std::string convert() const override;
  private:


};

#endif

