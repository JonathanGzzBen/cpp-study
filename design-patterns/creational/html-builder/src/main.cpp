#include <initializer_list>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

class HtmlElement {
 private:
  std::string tag_name;
  std::string text;
  std::vector<std::pair<std::string, std::string>> attributes;
  std::vector<HtmlElement> children;

 public:
  HtmlElement(std::string tag_name, std::string text)
      : tag_name{tag_name}, text{text} {}
  HtmlElement(std::string tag_name, std::vector<HtmlElement> children)
      : tag_name{tag_name}, children{children} {}

  HtmlElement& append_attribute(std::string name, std::string value) {
    attributes.emplace_back(std::make_pair(name, value));
    return *this;
  }

  friend class Img;
  friend std::ostream& operator<<(std::ostream& os, const HtmlElement& element);
};

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

class Html : public HtmlElement {
 public:
  Html() : HtmlElement("html", "") {}
  Html(std::initializer_list<HtmlElement> children)
      : HtmlElement("html", children) {}
};

class H1: public HtmlElement {
public:
	  H1(std::string text) : HtmlElement{"h1", text} {}
  H1(std::initializer_list<HtmlElement> children) : HtmlElement{"h1", children} {}
};

class P : public HtmlElement {
 public:
  P(std::string text) : HtmlElement{"p", text} {}
  P(std::initializer_list<HtmlElement> children) : HtmlElement{"p", children} {}
};

class Img : public HtmlElement {
 public:
  Img(std::string url) : HtmlElement{"img", ""} {
    attributes.emplace_back(std::make_pair("src", url));
  }
};

int main() {
  std::cout << Html{
  	H1{"Made in C++"}.append_attribute("style", "color: #4987bc; text-shadow: 2px 2px #f0d9ad;"),
      P{"This is the first HTML I write using C++"}.append_attribute(
          "style", "color: red;font-size:16px;"),
      Img{"https://w.wallhaven.cc/full/l3/wallhaven-l3xk6q.jpg"}
          .append_attribute("style", "width:100%;")};
  return 0;
}