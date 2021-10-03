#include "src/triangle.h"

Triangle::Triangle(int base, int height) : base{base}, height{height} {}

Triangle::~Triangle() {
  std::cout << "Deleting Triangle: " << *this << std::endl;
}

int Triangle::get_area() const { return (this->base * this->height) / 2; }

void Triangle::print(std::ostream &os) const {
  os << "Base: " << this->base << " Height: " << this->height;
}
