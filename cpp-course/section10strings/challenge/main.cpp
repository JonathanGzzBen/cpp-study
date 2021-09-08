/* Section 11
 * Challenge
 *
 * Make a cypher
 *
 */
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

int main() {
  cout << "Enter text to cypher: ";
  string input_text;
  getline(cin, input_text);
  cout << "Text to cypher: " << input_text << endl;

  string cypher_keys{"abcdefghijklmnopqrstuv "};
  string cypher_vals{"VUTSRQPOMNLKJIHGFEDCBA "};

  string cyphered_text;
  for (auto letter : input_text) {
    auto cypher_key_index{cypher_keys.find(letter)};
    cyphered_text += cypher_vals.at(cypher_key_index);
  }
  cout << "Cyphered text:" << endl;
  cout << cyphered_text << endl;

  string uncyphered_text;
  for (char letter : cyphered_text) {
    auto cypher_val_index{cypher_vals.find(letter)};
    uncyphered_text += cypher_keys.at(cypher_val_index);
  }
  cout << "Uncyphered text:" << endl;
  cout << uncyphered_text << endl;
}
