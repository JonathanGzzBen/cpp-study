#include "src/square.h"

Square::Square(int side) : side{side} {}

Square::~Square() { std::cout << "Deleting Square: " << *this << std::endl; }

int Square::get_area() const { return (this->side * this->side); }

void Square::print(std::ostream &os) const {
  os << "Square[Side:" << this->side << " Area:" << this->get_area() << "]";
}
