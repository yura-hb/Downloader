#include "HTMLRawTextTag.hpp"

const std::set<std::string> tags = {
  "script", "style"
};

HTMLElement::HTMLElementType HTMLRawTextTag::getElementType() const {
  return HTMLElement::HTMLElementType::RAW_TEXT;
}
