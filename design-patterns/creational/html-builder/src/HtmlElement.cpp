#include "HtmlElement.h"

#include <ostream>

HtmlElement& HtmlElement::append_attribute(std::string name,
                                           std::string value) {
  attributes.emplace_back(std::make_pair(name, value));
  return *this;
}

std::ostream& operator<<(std::ostream& os, const HtmlElement& element) {
  os << "<" << element.tag_name;
  for (const auto& [name, value] : element.attributes) {
    os << " " << name << "=\"" << value << "\"";
  }

  os << ">";

  if (element.text.length() != 0) {
    os << element.text;
  }

  for (const auto& child : element.children) {
    os << child;
  }

  os << "</" << element.tag_name << ">\n";
  return os;
}