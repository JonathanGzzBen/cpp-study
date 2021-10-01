#include "src/toybox.h"

#include <iostream>
#include <memory>
#include <string>

ToyBox::ToyBox(std::string name) : name{name} {}

ToyBox::~ToyBox() {
  std::cout << "Deleted toybox: " << this->name << std::endl;
}

std::string ToyBox::get_name() const { return this->name; }

bool ToyBox::set_name(std::string name) {
  this->name = name;
  return true;
}

std::vector<std::unique_ptr<Triangle>> &ToyBox::get_triangles() { return this->triangles; }
