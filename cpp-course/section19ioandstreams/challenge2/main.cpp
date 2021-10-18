/* Section 19
 * Challenge 2
 * Automated Grader
 *
 * Write a program that reads a file named 'responses.txt' that contains the
 * answer key for a quiz as well as student responses for the quiz.
 *
 * The answer key is the first item in the file.
 * Student1 name
 * Student1 responses
 * Student2 name
 * Student2 responses
 * ...
 *
 */
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>

int main() {
  std::ifstream responses_file{"responses.txt"};
  if (!responses_file.is_open()) {
    std::cerr << "Could not open responses.txt file" << std::endl;
  }
  std::cout << std::setw(20) << std::left << "Student"
            << "Score" << std::endl;
  std::string answer_keys;
  responses_file >> answer_keys;
  std::string student_name;
  std::string student_answers;
  while (responses_file >> student_name >> student_answers) {
    uint student_score{0};
    for (auto i{0}; i < answer_keys.length(); i++) {
      if (student_answers.at(i) == answer_keys.at(i)) {
        student_score++;
      }
    }
    std::cout << std::setw(20) << std::left << student_name << student_score << std::endl;
  }
  responses_file.close();
}
