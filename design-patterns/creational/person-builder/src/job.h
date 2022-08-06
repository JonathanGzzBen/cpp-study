#ifndef JOB_H
#define JOB_H

#include <string>

class JobBuilder;

class Job {
 private:
  std::string place;
  std::string role;

  Job() : place{""}, role{""} {}

 public:
  static JobBuilder create();

  inline std::string GetPlace() const { return place; }
  inline std::string GetRole() const { return role; }

  friend class JobBuilder;
  friend class Person;
};

#endif  // JOB_H