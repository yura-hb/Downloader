#include "HTMLNormalTag.hpp"

const std::vector<std::string> tags = {
  "template"
};

HTMLElement::HTMLElementType HTMLNormalTag::getElementType() const {
  return HTMLElement::HTMLElementType::TEMPLATE;
}
