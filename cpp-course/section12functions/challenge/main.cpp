/*
 * Section 9
 * Challenge
 *
 * This challenge is about using a collection (list) of integers and allowing
 * the user to select options from a menu to perform operations on the list.
 *
 * Your program should display a menu options to the user as follows:
 *
 * P - Print numbers
 * A - Add a number
 * M - Display mean of the numbers
 * S - Display the smallest number
 * L - Display the largest number
 * Q - Quit
 *
 * Enter your choice
 *
 * The program should only accept valid choices from the user, both upper and
 * lowercase selections should be allowed. If an illegal choice is made, you
 * should display, "Unknown selection, please try again" and the menu options
 * should be displayed again.
 *
 * If the user enters 'P' or 'p', you should display all of the elements (ints)
 * in the list. If the list is empty you should display "[] - the list is empty"
 * If the list is not empty then all the list element should be displayed inside
 * square brackets separated by a space. For example, [1 2 3 4 5]
 *
 * If the user enters 'A' or 'a' then you should prompt the user for an integer
 * to add to the list which you will add to the list and then display it was
 * added. For example, if the user enters 5 You should display, "5 added".
 * Duplicate list entries are OK
 *
 * If the user enters 'M' or 'm' you should calculate the mean or average of the
 * elements in the list and display it. If the list is empty you should display,
 * "Unable to calculate the mean - no data"
 *
 * If the user enters 'S' or 's' you should display the smallest element in the
 * list. For example, if the list contains [2 4 5 1], you should display, "The
 * smallest number is 1" If the list is empty you should display, "Unable to
 * determine the smallest number - list is empty"
 *
 * If the user enters 'L' or 'l' you should display the largest element in the
 * list. For example, if the list contains [2 4 5 1], you should display, "The
 * largest number is 5"
 *
 * If the list is empty you should display, "Unable to determine the largest
 * number - list is empty"
 *
 * If the user enters 'Q' or 'q' then you should display 'Goodbye' and the
 * program should terminate.
 *
 */

#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int read_element_to_add() {
  cout << "Enter element to add: ";
  int element_to_add{0};
  cin >> element_to_add;
  return element_to_add;
}

double get_mean(const vector<int> elements) {
  int sum{0};
  for (auto element : elements) {
    sum += element;
  }
  return static_cast<double>(sum) / elements.size();
}

int get_smallest_element(const vector<int> elements) {
  int smallest{elements.at(0)};
  for (auto element : elements) {
    if (element < smallest) smallest = element;
  }
  return smallest;
}

int get_largest_element(const vector<int> elements) {
  int largest{elements.at(0)};
  for (auto element : elements) {
    if (element > largest) largest = element;
  }
  return largest;
}

void read_and_add_element(vector<int> elements) {
    int new_element{read_element_to_add()};
    elements.push_back(new_element);
    cout << new_element << " added" << endl;
}

int main() {
  vector<int> elements;
  char user_selection;
  do {
    cout << endl << "P - Print numbers" << endl;
    cout << "A - Add a number" << endl;
    cout << "M - Display mean of the numbers" << endl;
    cout << "S - Display the smallest number" << endl;
    cout << "L - Display the largest number" << endl;
    cout << "Q - Quit" << endl << endl;
    cout << "Enter your choice: ";
    cin >> user_selection;
    cout << endl << endl;
    switch (user_selection) {
      case 'p':
      case 'P': {
        if (elements.size() > 0) {
            cout << "[";
          for (auto element : elements) {
            cout << element << " ";
          }
          cout << "\b \b]" << endl;
        } else {
          cout << "[] - the list is empty" << endl;
        }
        break;
      }
      case 'a':
      case 'A': {
        read_and_add_element(elements);
        break;
      }
      case 'm':
      case 'M': {
        if (elements.size() > 0) {
          cout << "Mean: " << get_mean(elements) << endl;
        } else {
          cout << "Unable to calculate the mean - no data";
        }
        break;
      }
      case 's':
      case 'S': {
        if (elements.size() > 0)
          cout << "The smallest number is " << get_smallest_element(elements)
               << endl;
        else
          cout << "Unable to determine the smallest number - list is empty"
               << endl;
        break;
      }
      case 'l':
      case 'L': {
        if (elements.size() > 0)
          cout << "The largest number is " << get_largest_element(elements)
               << endl;
        else
          cout << "Unable to determine the largest number - list is empty"
               << endl;
        break;
      }
      case 'q':
      case 'Q':
        cout << "See ya" << endl;
        break;
      default:
        cout << "Please enter a valid option from the menu." << endl;
    }
  } while (!(user_selection == 'Q' || user_selection == 'q'));
}
