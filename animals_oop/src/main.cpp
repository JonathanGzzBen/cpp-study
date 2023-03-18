#include <iostream>
#include <vector>

#include "rectangle.h"

int main() {

  // std::vector<Figure*> figures;
  // figures.emplace_back(new Rectangle{5,2});
  // for (const auto figure: figures) {
  //   figure->area();
  // }

  Figure* figure = new Rectangle{2, 4};
  delete figure;

  // Rectangle rectangle{5, 2};
  return 0;
}