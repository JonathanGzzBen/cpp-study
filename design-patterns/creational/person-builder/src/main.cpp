#include <iostream>
#include <string>

#include "job.h"
#include "job_builder.h"
#include "person.h"
#include "person_builder.h"

int main() {
  auto person =
      Person::create()
          .is_called("Jonathan")
          .age_in_years(21)
          .works(Job::create().at("Banregio").as_a("Software Developer"))
          .build();
  std::cout << person << std::endl;
  return 0;
}