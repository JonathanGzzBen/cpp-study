/**********************************************************
 * Section 8 Challenge
 *
 * For this program use US dollars and cents
 *
 * Write a program that asks the user to enter the following:
 * An integer representing the number of cents
 *
 * You may assume that the number of cents entered is greater than or equeal to
 *zero
 *
 * The program should then display how to provide that change to the user.
 *
 * In the US:
 *   1 dollar is 100 cents
 *   1 quarter is 25 cents
 *   1 dime is 10 cents
 *   1 nickel is 5 cents, and
 *   1 penny is 1 cent
 *
 *********************************************************/
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main() {
  cout << "Enter an amount in cents: ";
  int cents_number{0};
  cin >> cents_number;

  int balance{cents_number};
  int dollars{cents_number / 100};
  balance = cents_number % 100;
  int quarters{balance / 25};
  balance %= 25;
  int dimes{balance / 10};
  balance %= 10;
  int nickels{balance / 5};
  balance %= 5;
  int pennies{balance};
  balance = 0;
  cout << "dollars: " << dollars << endl;
  cout << "quarters: " << quarters << endl;
  cout << "dimes: " << dimes << endl;
  cout << "nickels: " << nickels << endl;
  cout << "pennies: " << pennies << endl;
}
