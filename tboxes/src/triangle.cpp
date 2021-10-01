#include "src/triangle.h"

Triangle::Triangle(int base, int height) {
  this->base = base;
  this->height = height;
}

Triangle::~Triangle() {
  std::cout << "Deleting Triangle: " << *this << std::endl;
}

int Triangle::get_area() const { return (this->base * this->height) / 2; }

std::ostream &operator<<(std::ostream &os, const Triangle &triangle) {
  return os << "Base: " << triangle.base << " Height: " << triangle.height;
}
