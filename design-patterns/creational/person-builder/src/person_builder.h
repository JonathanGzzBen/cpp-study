#ifndef PERSON_BUILDER_H
#define PERSON_BUILDER_H
#include "person.h"
#include <memory>

class PersonBuilder {
private:
  Person person;

public:
  PersonBuilder(Person &p) : person{p} {}
  PersonBuilder() {}

  PersonBuilder &name(std::string name) {
    person.name = name;
    return *this;
  }

  PersonBuilder &age(int years) {
    person.age = years;
    return *this;
  }

  PersonBuilder &job(Job job) {
    person.job = new Job{job};
    return *this;
  }

  PersonBuilder &job(Job *job) {
    person.job = job;
    return *this;
  }

  Person build() const { return std::move(person); }
  operator Person() const { return std::move(person); }
};

#endif // PERSON_BUILDER_H