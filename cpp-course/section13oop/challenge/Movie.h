#ifndef _MOVIE_H_
#define _MOVIE_H_
#include <iostream>
class Movie {
 private:
  std::string name;
  std::string rating;
  int watch_count;

 public:
  Movie () : Movie{"", "", 0} {
  }
  Movie(std::string name, std::string rating, int watch_count)
      : name{name}, rating{rating}, watch_count{watch_count} {}
  std::string get_name() const;
  void set_name(std::string name);
  std::string get_rating() const;
  void set_rating(std::string rating);
  int get_watch_count() const;
  void set_watch_count(int watch_count);
};
#endif
