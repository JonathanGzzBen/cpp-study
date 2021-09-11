/* Section 13
 * Challenge
 *
 * For this challenge you are to develop the foundation for a program
 * for movie fanatics to keep track of what movies they have watched
 * and how many times they watched a movie.
 *
 * The program must support the following:
 *
 * class Movie - models a movie which includes
 * - movie name
 * - movie rating (G, PG, PG-13, R)
 *
 * class Movies - models a collection o movie objects
 *
 * Obviously, Movies needs to know about Movie since it is a collection of Movie
 * object However, our main driver should only interact with the Movies class.
 *
 * For example, a simple main should be able to
 * - create a Movies object
 * - ask the Movies object to add a movie by providing the movie name, rating
 * and watched count
 * - ask the Movies object to increment the wached count by 1 for a movie given
 * its name
 * - ask the Movies object to display all of its movies
 *
 * Additionally,
 * - if we try to add a movie whose name is already in the movies collection
 *   we should display this error to the user
 * - if we try to increment the watched count for a movie whose name is not in
 * the movies collection we should display this error to the user
 */
#include <iostream>

int main() {
    std::cout<< "Hey" << std::endl;
}

