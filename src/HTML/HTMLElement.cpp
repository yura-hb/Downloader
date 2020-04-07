#include "HTMLElement.hpp"

std::string HTMLElement::getElementName() const { return elementName; }
std::vector<std::shared_ptr<HTMLElement>> HTMLElement::getChildren() const { return children; }
std::map<std::string, std::string> HTMLElement::getAttributes() const { return attributes; }
