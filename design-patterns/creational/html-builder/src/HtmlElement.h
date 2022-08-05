#ifndef HTML_ELEMENT_H
#define HTML_ELEMENT_H

#include <string>
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

  HtmlElement& append_attribute(std::string name, std::string value);

  friend class Img;
  friend std::ostream& operator<<(std::ostream& os, const HtmlElement& element);
};

class Html : public HtmlElement {
 public:
  Html() : HtmlElement("html", "") {}
  Html(std::initializer_list<HtmlElement> children)
      : HtmlElement("html", children) {}
};

class H1 : public HtmlElement {
 public:
  H1(std::string text) : HtmlElement{"h1", text} {}
  H1(std::initializer_list<HtmlElement> children)
      : HtmlElement{"h1", children} {}
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

#endif  // HTML_ELEMENT_H
