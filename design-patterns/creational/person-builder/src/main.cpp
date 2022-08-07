#include <iostream>
#include <string>

#include "job.h"
#include "job_builder.h"
#include "person.h"
#include "person_builder.h"

int main() {
  auto person =
      Person::create()
          .name("Jonathan")
          .age(21)
          .job(Job::create().place("Banregio").role("Software Developer"))
          .build();
  std::cout << person << std::endl;
  return 0;
}