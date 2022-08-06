#include <iostream>
#include <string>

#include "person.h"

struct Address {
  std::string country;
  std::string street_addres;
  int post_code;
};

int main() {
  auto person = Person::create().is_called("Jonathan").has_age(20);
  std::cout << person << std::endl;
  return 0;
}