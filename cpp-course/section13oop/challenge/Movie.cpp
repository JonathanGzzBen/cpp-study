#include "Movie.h"

#include <string>

std::string Movie::get_name() const { return name; }
void Movie::set_name(std::string name) { this->name = name; }

std::string Movie::get_rating() const { return rating; }
void Movie::set_rating(std::string rating) { this->rating = rating; }

int Movie::get_watch_count() const { return watch_count; }

void Movie::set_watch_count(int watch_count) {
  this->watch_count = watch_count;
}
