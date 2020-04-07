#ifndef __HTML_ELEMENT_H__
#define __HTML_ELEMENT_H__

#include <iostream>
#include "map"
#include "StringConvertible.hpp"
/**
 * Abstract struct to generalize logic of HTMLElement
 */

struct HTMLElement: public StringConvertible {
  enum class HTMLElementType {
    VOID,
    TEMPLATE,
    TEXTELEMENT,
    ESCAPABLE,
    FOREIGN_ELEMENT,
    NORMAL
  };


  virtual const std::string getTagName();
  /**
   * Returns type of the HTML element
   */
  virtual const HTMLElementType getType() = 0;
  virtual const std::string getData();
  virtual const std::map<std::string, std::string> getAttributes() const;
  virtual const std::vector<HTMLElement> getChildren() const;
  virtual std::string convert() const = 0;

  virtual ~HTMLElement() = 0;
};

#endif
