#include "Movies.h"

#include <vector>

void Movies::add_movie(Movie movie) { movies.push_back(movie); }

void Movies::add_movie(std::string name, std::string rating,
                       int watched_count) {
  movies.push_back({name, rating, watched_count});
}

void Movies::increment_watched_count(std::string movie_name) {
  for (auto &movie : movies) {
    if (movie.get_name() == movie_name) {
      movie.set_watch_count(movie.get_watch_count() + 1);
    }
  }
}

std::vector<Movie> Movies::get_movies() const { return movies; }
