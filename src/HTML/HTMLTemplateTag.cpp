#include "HTMLTemplateTag.hpp"

const std::set<std::string> tags = {
  "template"
};

HTMLElement::HTMLElementType HTMLTemplateTag::getElementType() const {
  return HTMLElement::HTMLElementType::TEMPLATE;
}
