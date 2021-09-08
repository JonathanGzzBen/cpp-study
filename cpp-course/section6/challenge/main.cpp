/* Frank's Carpet Cleaning Service
 * Charges:
 * $25 per small room
 * $35 per large room
 * Sales tax rate is 6%
 * Estimates are valid for 30 days
 *
 * Prompt the user for the number of small and large rooms they would like
 * cleaned and provide an estime such as:
 *
 * Estimate for carpet cleaning service
 * Number of small rooms: 3
 * Number of large rooms: 1
 * Price per small room: $25
 * Price per large room: $35
 * Cost: $110
 * Tax: $5.5
 * ============================
 * Total estimate: $116.6
 * This estimate is valid for 30 days
 */

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char const *argv[]) {
  const int price_per_small_room{25};
  const int price_per_large_room{35};
  const float tax_rate{0.06};
  const int validity_in_days{30};

  int small_rooms_to_clean{0};
  int large_rooms_to_clean{0};

  cout << "Specify amount of rooms to be cleaned:" << endl;
  cout << "Small rooms: ";
  cin >> small_rooms_to_clean;
  cout << "Large rooms: ";
  cin >> large_rooms_to_clean;

  int cost{(small_rooms_to_clean * price_per_small_room) +
           (large_rooms_to_clean * price_per_large_room)};

  float tax{cost * tax_rate};

  float total_cost{cost + tax};

  cout << "Estimate for carpet cleaning service" << endl;
  cout << "Number of small rooms: " << small_rooms_to_clean << endl;
  cout << "Number of large rooms: " << large_rooms_to_clean << endl;
  cout << "Price per small room: $" << price_per_small_room << endl;
  cout << "Price per large room: $" << price_per_large_room << endl;
  cout << "Cost: " << cost << endl;
  cout << "Tax: " << tax << endl;
  cout << "===========================" << endl;
  cout << "Total estimate: " << total_cost << endl;
  cout << "This estimate is valid for " << validity_in_days << " days" << endl;

  return 0;
}
