#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <memory>
#include <ostream>
#include <string>

#include "job.h"

class PersonBuilder;

class Person {
private:
  std::string name;
  int age;
  std::shared_ptr<Job> job;

  Person() : name{""}, age{0}, job{nullptr} {}

public:
  static PersonBuilder create();

  inline std::string GetName() const { return name; }
  inline int GetAge() const { return age; }
  inline Job GetJob() const { return *job; }

  friend class PersonBuilder;
  friend std::ostream &operator<<(std::ostream &os, const Person &dt);
};

#endif // PERSON_H