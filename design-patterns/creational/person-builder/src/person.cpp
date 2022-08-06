#include "person.h"

static Person::Builder create() { return Person::Builder{}; }

Person::Builder& Person::Builder::is_called(std::string name) {
  this->name = name;
  return *this;
}

Person::Builder& Person::Builder::has_age(int years) {
  this->age = years;
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Person& person) {
  os << "Name: " << person.name << "\nAge: " << person.age;
  return os;
}