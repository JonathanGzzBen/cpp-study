#ifndef _MOVIES_H
#define _MOVIES_H
#include <vector>

#include "Movie.h"

class Movies {
 private:
  std::vector<Movie> movies;

 public:
  void add_movie(Movie movie);
  void add_movie(std::string name, std::string rating, int watched_count);
  void increment_watched_count(std::string movie_name);
  std::vector<Movie> get_movies() const;
};
#endif
