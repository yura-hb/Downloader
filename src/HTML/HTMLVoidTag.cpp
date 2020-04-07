#include "HTMLVoidTag.hpp"

const std::set<std::string> tags = {
  "area", "base", "br", "col", "embed", "hr", "img", "input", "link", "meta", "param", "source", "track", "wbr"
};

HTMLElement::HTMLElementType HTMLVoidTag::getElementType() const {
  return HTMLElement::HTMLElementType::VOID;
}
