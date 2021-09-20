#include "src/toybox.h"

#include <iostream>
#include <string>

ToyBox::ToyBox(std::string name) : name{name} {}

ToyBox::~ToyBox() {
  for (const auto &triangle : this->triangles) {
    std::cout << "Deleting triangle" << std::endl;
    delete triangle;
  }
  std::cout << "Deleted toybox: " << this->name << std::endl;
}

std::string ToyBox::get_name() const { return this->name; }

bool ToyBox::set_name(std::string name) {
  this->name = name;
  return true;
}

std::vector<Triangle *> ToyBox::get_triangles() { return this->triangles; }
