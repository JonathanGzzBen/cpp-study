#ifndef PERSON_BUILDER_H
#define PERSON_BUILDER_H
#include "person.h"

class PersonBuilder {
 private:
  Person person;

 public:
  PersonBuilder(Person& p) : person{p} {}
  PersonBuilder() {}

  PersonBuilder& is_called(std::string name) {
    person.name = name;
    return *this;
  }

  PersonBuilder& age_in_years(int years) {
    person.age = years;
    return *this;
  }

  PersonBuilder& works(Job job) {
    person.job = job;
    return *this;
  }

  Person build() const { return std::move(person); }
  operator Person() const { return std::move(person); }
};

#endif  // PERSON_BUILDER_H