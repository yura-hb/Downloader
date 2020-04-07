#ifndef __HTML_ELEMENT_H__
#define __HTML_ELEMENT_H__

#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include "../Templates/StringConvertible.hpp"

struct HTMLElement: public StringConvertible {
    /**
     *  List of basic HTML elements types
     */
    enum class HTMLElementType {
      VOID,
      TEMPLATE,
      TEXTELEMENT,
      ESCAPABLE,
      FOREIGN_ELEMENT,
      NORMAL
    };

    HTMLElement(const std::string& elementName,
                const std::string& data = "",
                const std::map<std::string, std::string>& attributes = {},
                const std::vector<std::shared_ptr<HTMLElement>>& childen = {}):
                elementName(elementName), data(data), attributes(attributes), children(childen) {}
    /**
     *  Loads element type, there are six of them and each of them can have different type of parsing
     */
    virtual HTMLElementType getElementType() const = 0;
    /**
     *  Loads the name of the element
     */
    virtual std::string getElementName() const;
    /**
     *  Loads attributes
     */
    virtual std::map<std::string, std::string> getAttributes() const;
    /**
     *  Load children
     */
    virtual std::vector<std::shared_ptr<HTMLElement>> getChildren() const;

    virtual ~HTMLElement() noexcept = default;
  protected:
    std::string elementName = "";
    std::string data = "";
    std::map<std::string, std::string> attributes = {};
    std::vector<std::shared_ptr<HTMLElement>> children = {};
};

#endif
