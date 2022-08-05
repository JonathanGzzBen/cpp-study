#include <initializer_list>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "HtmlElement.h"

int main() {
  std::cout << Html{
      H1{"Made in C++"}.append_attribute(
          "style", "color: #4987bc; text-shadow: 2px 2px #f0d9ad;"),
      P{"This is the first HTML I write using C++"}.append_attribute(
          "style", "color: red;font-size:16px;"),
      Img{"https://w.wallhaven.cc/full/l3/wallhaven-l3xk6q.jpg"}
          .append_attribute("style", "width:100%;")};
  return 0;
}