/* Section 20
 * Challenge 3
 * Using std::set and std::map
 *
 * This challenge has 2 parts.
 * We will be reading words from a text file provided to you.
 * The text file is named 'words.txt' and contains the first few
 * paragraphs from the book, "The Wonderful Wizard of Oz".
 *
 * Part 1:
 * For part 1 of this challenge, you are to display each unique word
 * in the file and immediately following each word display the number
 * of time it occurs in the text file.
 *
 * The words should be displayed in ascending order.
 *
 * Here is a sample listing of the first few words:
 *
 * Word      Count
 * =====================================
 * Aunt      5
 * Dorothy   8
 *
 * Please use a map with <string, int> Key/Value pairs
 *
 * ==========================================================
 * Part 2:
 * For part 2 of this challenge, you are to display each unique word
 * in the file and immediately following each word display the line numbers
 * in which that word appears.
 *
 * The words should be displayed in ascending order and the line numbers for
 * each word should also bse displayed in ascending order.
 *
 * If a word appears more than once on a line then the line number should
 * only appear once.
 *
 * Word      Occurrences
 * =====================================
 * Aunt      [2 7 25 29 48]
 * Dorothy   [1 7 15 29 39 43 47 51]
 *
 */
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

int main() {
  std::ifstream words_file{"words.txt"};
  std::map<std::string, int> word_count{};
  if (!words_file.is_open()) {
    std::cout << "Could not open file words.txt" << std::endl;
    return 0;
  }
  // Part 1
  std::cout << std::setw(20) << std::left << "Word"
            << "Count" << std::endl;
  std::cout << "======================================" << std::endl;
  while (!words_file.eof()) {
    std::string word;
    words_file >> word;
    word_count[word]++;
  }
  for (auto w : word_count) {
    std::cout << std::setw(20) << std::left << w.first << " " << w.second
              << std::endl;
  }
  words_file.close();
  // Part 2
  words_file.open("words.txt");
  std::cout << std::setw(20) << std::left << "Word"
            << "Occurrences" << std::endl;
  std::cout << "======================================" << std::endl;
  std::map<std::string, std::list<int>> word_occurrences;
  int line_number{0};
  std::string line;
  while (std::getline(words_file, line)) {
    line_number++;
    std::stringstream ss{line};
    std::string word;
    ss >> word;
    word_occurrences[word].push_back(line_number);
  }
  for (auto w : word_occurrences) {
    std::cout << std::setw(20) << std::left << w.first << " [ ";
    for (auto line_number : w.second) {
      std::cout << line_number << " ";
    }
    std::cout << "]" << std::endl;
  }

  words_file.close();
}
