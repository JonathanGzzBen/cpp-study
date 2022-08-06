#ifndef PERSON_H
#define PERSON_H

#include <ostream>
#include <string>

class Person {
 private:
  std::string name;
  int age;

 public:
  class Builder {
   private:
    std::string name = "";
    int age = 0;

   public:
    Builder& is_called(std::string name);
    Builder& has_age(int years);
    Person build() { return Person(*this); }
    friend class Person;
  };

  Person(Builder builder) : name{builder.name}, age{builder.age} {}

  static Builder create() { return Builder{}; }

  friend std::ostream& operator<<(std::ostream& os, const Person& dt);
};

#endif  // PERSON_H