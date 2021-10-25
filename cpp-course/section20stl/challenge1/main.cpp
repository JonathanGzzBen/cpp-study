/* Section 20
 * Challenge 1 - Deque Challenge
 *
 * A palindrome is a string that reads the same backwards or forwards.
 * Only consider alpha characters and omit all other characters.
 *
 * Write the function:
 * bool is_palindrome(const std::string &s);
 *
 * Use a deque to solve the problem
 */
#include <cctype>
#include <deque>
#include <iostream>
#include <string>

bool is_palindrome(const std::string &s);
void print_message_is_palindrome(const std::string &s);

int main() {
  std::string string1{"madam"};
  std::string string2{"Jonathan"};
  print_message_is_palindrome(string1);
  print_message_is_palindrome(string2);
}

void print_message_is_palindrome(const std::string &s) {
  std::cout << s << (is_palindrome(s) ? " is" : " is not") << " palindrome"
            << std::endl;
}

bool is_palindrome(const std::string &s) {
  std::deque<char> d;
  for (auto c : s) {
    if (std::isalpha(c)) {
      d.push_back(std::toupper(c));
    }
  }
  char c1;
  char c2;
  while (d.size() > 1) {
    c1 = d.front();
    c2 = d.back();
    if (c1 != c2) {
      return false;
    }
    d.pop_front();
    d.pop_back();
  }
  return true;
}
