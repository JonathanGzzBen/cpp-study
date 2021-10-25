/* Section 20
 * Challenge 2
 *
 * In this challenge you will create a menu driven application that
 * will simulate a user playing songs from a playlist of songs.
 *
 * We sill use a list to simulate the user selecting the first song in the
 * playlist then selecting next and previous to play forward or backwards
 * through the playlist.
 *
 * We will also allow users to add new song to the playlist and they will be
 * added prior to the currently playing songs.
 *
 * The menu looks as follows:
 *
 * F - Play First Song
 * N - Play Next Song
 * P - Play Previous Song
 * A - Add and play a new Song at current location
 * L - List the current playlist
 * ==================================================
 * Enter a selection (Q to quit):
 *
 * And the available playlist is modeled as a std::list<Song>
 *
 *
 */
#include <cstdio>
#include <deque>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>

class Song {
  friend std::ostream& operator<<(std::ostream& os, Song const& s) {
    return os << std::setw(30) << std::left << s.Name << std::setw(40)
              << std::left << s.Artist;
  }

 public:
  Song(std::string artist, std::string name) : Artist{artist}, Name{name} {}
  std::string Artist;
  std::string Name;
};

void print_songs(const std::deque<Song>& playlist);
char get_menu_input();

int main() {
  std::deque<Song> playlist;
  playlist.emplace_back("Imagine Dragons", "It's time");
  playlist.emplace_back("Skillet", "Not Gonna Die");
  playlist.emplace_back("Rectifire", "Stay");
  auto current_song{playlist.cbegin()};
  char input{};
  while (!(input == 'q' || input == 'Q')) {
    std::cout << "Current Song:" << std::endl;
    std::cout << *current_song << std::endl;
    input = get_menu_input();
    switch (input) {
      case 'f':
      case 'F': {
        current_song = playlist.cbegin();
        break;
      }
      case 'n':
      case 'N': {
        current_song++;
        if (current_song == playlist.cend()) {
          current_song = playlist.cbegin();
        }
        break;
      }
      case 'p':
      case 'P': {
        if (current_song == playlist.cbegin()) {
          current_song = playlist.cend();
        }
        current_song--;
        break;
      }
      case 'a':
      case 'A': {
        std::string artist;
        std::cout << "Artist: ";
        std::getline(std::cin >> std::ws, artist);
        std::string name;
        std::cout << "Name: ";
        std::getline(std::cin >> std::ws, name);
        current_song = playlist.emplace(++current_song, artist, name);
        break;
      }
      case 'l':
      case 'L': {
        print_songs(playlist);
        break;
      }
    }
  }
}

void print_songs(const std::deque<Song>& playlist) {
  for (auto song : playlist) {
    std::cout << song << std::endl;
  }
}

char get_menu_input() {
  std::cout << "F - Play First Song" << std::endl;
  std::cout << "N - Play Next Song" << std::endl;
  std::cout << "P - Play Previous Song" << std::endl;
  std::cout << "A - Add and play a new Song at current location" << std::endl;
  std::cout << "L - List the current playlist" << std::endl;
  std::cout << "=========================================" << std::endl;
  std::cout << "Enter a selection (Q to quit): ";
  char input;
  std::cin >> input;
  return input;
}
