#include "person.h"

#include <string>

#include "person_builder.h"

PersonBuilder Person::create() { return PersonBuilder(); }

std::ostream& operator<<(std::ostream& os, const Person& person) {
  os << "Name: " << person.name << "\nAge: " << person.age;
  if (person.job.GetPlace().length() != 0) {
    os << "\nWorks at: " << person.job.GetPlace();
  }
  if (person.job.GetRole().length() != 0) {
    os << "\nRole: " << person.job.GetRole();
  }
  return os;
}